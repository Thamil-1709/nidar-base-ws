#!/usr/bin/env python3
"""
ScoutMissionManager (OFFBOARD / TrajectorySetpoint version)

- Arms vehicle
- Switches to OFFBOARD
- Converts GeoPoint waypoints -> local NED (meters) relative to first GPS fix (home)
- Streams TrajectorySetpoint at 20 Hz while moving to each waypoint
- Publishes action feedback with current GPS location
- Returns to home and lands at the end
"""

from pyproj import Proj, Transformer
import math
import time

import rclpy
from rclpy.node import Node
from rclpy.action import ActionServer, GoalResponse, CancelResponse
from rclpy.qos import QoSProfile, QoSReliabilityPolicy

from px4_msgs.msg import VehicleCommand, VehicleGlobalPosition, TrajectorySetpoint, VehicleStatus
from geographic_msgs.msg import GeoPoint
from mission_interfaces.action import ScoutActionTrigger

# Tuning
SETPOINT_PUBLISH_HZ = 20.0
WAYPOINT_POS_TOL_M = 2.5    # horizontal tolerance (meters)
WAYPOINT_ALT_TOL_M = 1.5    # altitude tolerance (meters)
WAYPOINT_TIMEOUT_S = 120.0  # per-waypoint timeout
PREFLIGHT_TIMEOUT_S = 30.0  # preflight checks timeout

class ScoutMissionManager(Node):
    def __init__(self):
        super().__init__('scout_mission_manager_offboard')
        self.get_logger().info('Scout Mission Manager (offboard) initializing...')

        # Action server
        self._action_server = ActionServer(
            self,
            ScoutActionTrigger,
            'start_scan',
            execute_callback=self.execute_callback,
            goal_callback=self.goal_callback,
            cancel_callback=self.cancel_callback,
        )

        # Publishers
        self.cmd_pub = self.create_publisher(VehicleCommand, '/fmu/in/vehicle_command', 10)
        self.traj_pub = self.create_publisher(TrajectorySetpoint, '/fmu/in/trajectory_setpoint', 10)

        # PX4 telemetry subscription (BEST_EFFORT)
        qos = QoSProfile(depth=10)
        qos.reliability = QoSReliabilityPolicy.BEST_EFFORT

        self.create_subscription(VehicleGlobalPosition,
                                 '/fmu/out/vehicle_global_position',
                                 self.global_position_cb,
                                 qos)
        self.create_subscription(VehicleStatus,
                                 '/fmu/out/vehicle_status',
                                 self.vehicle_status_cb,
                                 qos)

        # state
        self.current_lat = None   # degrees
        self.current_lon = None
        self.current_alt = None   # meters AMSL
        self.home_lat = None
        self.home_lon = None
        self.home_alt = None
        
        self.armed_state = VehicleStatus.ARMING_STATE_DISARMED
        self.nav_state = VehicleStatus.NAVIGATION_STATE_MANUAL

        # transformer: created when home is set
        self._proj_wgs84 = None
        self._proj_aeqd = None
        self._transformer = None

        self.get_logger().info('Scout Mission Manager ready (offboard).')

    # -------------------------- PX4 / GPS callbacks --------------------------
    def global_position_cb(self, msg: VehicleGlobalPosition):
        lat = msg.lat
        lon = msg.lon
        alt = msg.alt
        if isinstance(lat, int) or abs(lat) > 1e6:
            self.current_lat = float(lat) * 1e-7
        else:
            self.current_lat = float(lat)
        if isinstance(lon, int) or abs(lon) > 1e6:
            self.current_lon = float(lon) * 1e-7
        else:
            self.current_lon = float(lon)
        if abs(alt) > 1e4:
            self.current_alt = float(alt) * 1e-3
        else:
            self.current_alt = float(alt)

        if (self.home_lat is None) and (self.current_lat is not None) and (self.current_lon is not None):
            if not (self.current_lat == 0.0 and self.current_lon == 0.0):
                self.home_lat = self.current_lat
                self.home_lon = self.current_lon
                self.home_alt = self.current_alt
                self._init_transformers()
                self.get_logger().info(f'Home set: {self.home_lat:.6f}, {self.home_lon:.6f}, {self.home_alt:.2f} m')

    def vehicle_status_cb(self, msg: VehicleStatus):
        self.armed_state = msg.arming_state
        self.nav_state = msg.nav_state
        
    def _init_transformers(self):
        self._proj_wgs84 = Proj(proj='latlong', ellps='WGS84')
        self._proj_aeqd = Proj(proj='aeqd', lat_0=self.home_lat, lon_0=self.home_lon, ellps='WGS84')
        self._transformer = Transformer.from_proj(self._proj_wgs84, self._proj_aeqd, always_xy=True)

    # -------------------------- Helpers --------------------------
    def send_vehicle_command(self, command, param1=0.0, param2=0.0, param3=0.0,
                             param4=0.0, param5=0.0, param6=0.0, param7=0.0):
        msg = VehicleCommand()
        msg.param1 = float(param1)
        msg.param2 = float(param2)
        msg.param3 = float(param3)
        msg.param4 = float(param4)
        msg.param5 = float(param5)
        msg.param6 = float(param6)
        msg.param7 = float(param7)
        msg.command = int(command)
        msg.target_system = 1
        msg.target_component = 1
        msg.source_system = 1
        msg.source_component = 1
        msg.from_external = True
        msg.timestamp = int(self.get_clock().now().nanoseconds // 1000)
        self.cmd_pub.publish(msg)

    def geo_to_local_ned(self, lat, lon, alt):
        if self._transformer is None:
            raise RuntimeError('Home not set -> cannot convert geo -> local')
        east, north = self._transformer.transform(lon, lat)
        x_n = float(north)
        y_e = float(east)
        z_d = float(-(alt - self.home_alt))
        return x_n, y_e, z_d

    def local_distance(self, target_n, target_e, target_d):
        if self.current_lat is None:
            return float('inf')
        cur_n, cur_e, cur_d = self.geo_to_local_ned(self.current_lat, self.current_lon, self.current_alt)
        dn = target_n - cur_n
        de = target_e - cur_e
        dd = target_d - cur_d
        return math.sqrt(dn*dn + de*de + dd*dd)
    
    def abort_mission(self, goal_handle, error_msg):
        self.get_logger().error(error_msg)
        goal_handle.abort()
        res = ScoutActionTrigger.Result()
        res.success = False
        return res

    # -------------------------- Action callbacks --------------------------
    def goal_callback(self, goal_request):
        self.get_logger().info('Received scout goal request.')
        return GoalResponse.ACCEPT

    def cancel_callback(self, goal_handle):
        self.get_logger().info('Cancel request received.')
        return CancelResponse.ACCEPT

    def execute_callback(self, goal_handle):
        self.get_logger().info('Execute: scout mission started.')
        waypoints = goal_handle.request.waypoints
        
        # Check pre-flight conditions
        timeout_start = time.time()
        self.get_logger().info('Waiting for preflight conditions (GPS fix, disarmed)...')
        while (time.time() - timeout_start < PREFLIGHT_TIMEOUT_S):
            rclpy.spin_once(self, timeout_sec=0.1)
            # Ensure GPS fix, disarmed state, and proper mode for takeoff
            if (self.home_lat is not None and 
                self.armed_state == VehicleStatus.ARMING_STATE_DISARMED):
                self.get_logger().info('Preflight checks passed: GPS fix and vehicle disarmed.')
                break
        
        if time.time() - timeout_start >= PREFLIGHT_TIMEOUT_S:
            return self.abort_mission(goal_handle, 'Preflight timeout. Aborting mission. Check system health.')

        if len(waypoints) == 0:
            return self.abort_mission(goal_handle, 'No waypoints provided. Aborting.')

        # ----------------- Start streaming setpoints for OFFBOARD mode -----------------
        self.get_logger().info('Streaming initial setpoints to enable OFFBOARD...')
        start_time = time.time()
        while time.time() - start_time < 2.0:
            if goal_handle.is_cancel_requested:
                return self.abort_mission(goal_handle, 'Goal cancel requested during pre-flight.')
            
            sp = TrajectorySetpoint()
            sp.timestamp = int(self.get_clock().now().nanoseconds // 1000)
            # Hold at current position to enable OFFBOARD
            cur_n, cur_e, cur_d = self.geo_to_local_ned(self.current_lat, self.current_lon, self.current_alt)
            sp.position = [float(cur_n), float(cur_e), float(cur_d)]
            sp.yaw = 0.0
            self.traj_pub.publish(sp)
            time.sleep(1.0 / SETPOINT_PUBLISH_HZ)
            rclpy.spin_once(self, timeout_sec=0.01)

        # ----------------- SWITCH TO OFFBOARD & ARM -----------------
        self.get_logger().info('Requesting OFFBOARD mode and arming...')
        self.send_vehicle_command(VehicleCommand.VEHICLE_CMD_DO_SET_MODE, param1=1.0, param2=6.0) # OFFBOARD mode
        self.send_vehicle_command(VehicleCommand.VEHICLE_CMD_COMPONENT_ARM_DISARM, param1=1.0) # Arm
        
        # Wait for vehicle to be armed and in OFFBOARD mode
        timeout_start = time.time()
        while (time.time() - timeout_start < 10.0):
            if goal_handle.is_cancel_requested:
                return self.abort_mission(goal_handle, 'Goal cancel requested while arming.')
            
            rclpy.spin_once(self, timeout_sec=0.1)
            if (self.armed_state == VehicleStatus.ARMING_STATE_ARMED and 
                self.nav_state == VehicleStatus.NAVIGATION_STATE_OFFBOARD):
                self.get_logger().info('Vehicle armed and in OFFBOARD mode.')
                break
            
            # Continuously stream setpoints
            sp = TrajectorySetpoint()
            sp.timestamp = int(self.get_clock().now().nanoseconds // 1000)
            cur_n, cur_e, cur_d = self.geo_to_local_ned(self.current_lat, self.current_lon, self.current_alt)
            sp.position = [float(cur_n), float(cur_e), float(cur_d)]
            sp.yaw = 0.0
            self.traj_pub.publish(sp)
            time.sleep(1.0 / SETPOINT_PUBLISH_HZ)

        if not (self.armed_state == VehicleStatus.ARMING_STATE_ARMED and self.nav_state == VehicleStatus.NAVIGATION_STATE_OFFBOARD):
            return self.abort_mission(goal_handle, 'Failed to arm or switch to OFFBOARD mode. Aborting.')

        # ----------------- Climb to safe altitude -----------------
        climb_alt = (self.current_alt or self.home_alt) + 8.0
        self.get_logger().info(f'Climb target alt (AMSL): {climb_alt:.2f} m')
        target_n0, target_e0, target_d0 = self.geo_to_local_ned(self.home_lat, self.home_lon, climb_alt)

        climb_start = time.time()
        while True:
            if goal_handle.is_cancel_requested or self.nav_state != VehicleStatus.NAVIGATION_STATE_OFFBOARD:
                return self.abort_mission(goal_handle, 'Mission aborted during climb. OFFBOARD mode lost.')

            sp = TrajectorySetpoint()
            sp.timestamp = int(self.get_clock().now().nanoseconds // 1000)
            sp.position = [float(target_n0), float(target_e0), float(target_d0)]
            sp.yaw = 0.0
            self.traj_pub.publish(sp)

            rclpy.spin_once(self, timeout_sec=0.01)
            time.sleep(1.0/SETPOINT_PUBLISH_HZ)
            
            if self.current_alt is not None and abs(self.current_alt - climb_alt) <= WAYPOINT_ALT_TOL_M:
                self.get_logger().info(f'Reached climb altitude ~{self.current_alt:.2f} m')
                break

            if time.time() - climb_start > 30.0:
                self.get_logger().warn('Climb timeout; continuing mission with current altitude.')
                break

        # ----------------- Visit waypoints -----------------
        for idx, gp in enumerate(waypoints):
            if goal_handle.is_cancel_requested or self.nav_state != VehicleStatus.NAVIGATION_STATE_OFFBOARD:
                return self.abort_mission(goal_handle, f'Mission aborted. OFFBOARD mode lost or cancel requested at WP {idx+1}.')
            
            wp_lat, wp_lon, wp_alt = float(gp.latitude), float(gp.longitude), float(gp.altitude)
            tgt_n, tgt_e, tgt_d = self.geo_to_local_ned(wp_lat, wp_lon, wp_alt)
            self.get_logger().info(f'Moving to WP {idx+1}/{len(waypoints)} -> NED: n={tgt_n:.2f} e={tgt_e:.2f} d={tgt_d:.2f}')

            wp_start = time.time()
            reached = False
            while not reached and (time.time() - wp_start) < WAYPOINT_TIMEOUT_S and rclpy.ok():
                if self.nav_state != VehicleStatus.NAVIGATION_STATE_OFFBOARD:
                    return self.abort_mission(goal_handle, 'OFFBOARD mode lost during waypoint navigation.')

                sp = TrajectorySetpoint()
                sp.timestamp = int(self.get_clock().now().nanoseconds // 1000)
                sp.position = [float(tgt_n), float(tgt_e), float(tgt_d)]
                sp.yaw = 0.0
                self.traj_pub.publish(sp)

                fb = ScoutActionTrigger.Feedback()
                curr = GeoPoint()
                curr.latitude = float(self.current_lat or 0.0)
                curr.longitude = float(self.current_lon or 0.0)
                curr.altitude = float(self.current_alt or 0.0)
                fb.current_location = curr
                goal_handle.publish_feedback(fb)

                rclpy.spin_once(self, timeout_sec=0.01)
                time.sleep(1.0/SETPOINT_PUBLISH_HZ)

                dist = self.local_distance(tgt_n, tgt_e, tgt_d)
                if dist <= WAYPOINT_POS_TOL_M:
                    self.get_logger().info(f'Reached WP {idx+1} (dist {dist:.2f} m)')
                    reached = True

            if not reached:
                return self.abort_mission(goal_handle, f'WP {idx+1} not reached within timeout. Aborting.')

        # ----------------- Return to home and Land -----------------
        if self.home_lat is not None:
            approach_alt = self.home_alt + 6.0
            tgt_n, tgt_e, tgt_d = self.geo_to_local_ned(self.home_lat, self.home_lon, approach_alt)
            self.get_logger().info(f'Returning to home (approach alt {approach_alt:.2f})')
            home_start = time.time()
            while rclpy.ok():
                if self.nav_state != VehicleStatus.NAVIGATION_STATE_OFFBOARD:
                    return self.abort_mission(goal_handle, 'OFFBOARD mode lost during return-to-home sequence.')
                
                sp = TrajectorySetpoint()
                sp.timestamp = int(self.get_clock().now().nanoseconds // 1000)
                sp.position = [float(tgt_n), float(tgt_e), float(tgt_d)]
                sp.yaw = 0.0
                self.traj_pub.publish(sp)

                rclpy.spin_once(self, timeout_sec=0.01)
                time.sleep(1.0/SETPOINT_PUBLISH_HZ)

                dist = self.local_distance(tgt_n, tgt_e, tgt_d)
                if dist <= WAYPOINT_POS_TOL_M:
                    self.get_logger().info('Over home approach point.')
                    break
                if time.time() - home_start > 60.0:
                    self.get_logger().warn('Timeout returning to home; proceeding to land now.')
                    break
        
        # ----------------- Land (using VEHICLE_CMD_NAV_LAND) -----------------
        self.get_logger().info('Sending LAND command.')
        self.send_vehicle_command(VehicleCommand.VEHICLE_CMD_NAV_LAND, param5=self.home_lat or 0.0, param6=self.home_lon or 0.0, param7=self.home_alt or 0.0)
        
        land_start = time.time()
        while rclpy.ok() and self.nav_state != VehicleStatus.NAVIGATION_STATE_AUTO_LAND and time.time() - land_start < 10.0:
            rclpy.spin_once(self, timeout_sec=0.1)

        if self.nav_state != VehicleStatus.NAVIGATION_STATE_AUTO_LAND:
            return self.abort_mission(goal_handle, 'Failed to switch to LAND mode. Mission incomplete.')
        
        # mission complete
        self.get_logger().info('Mission finished — marking result SUCCESS.')
        goal_handle.succeed()
        res = ScoutActionTrigger.Result()
        res.success = True
        return res

def main(args=None):
    rclpy.init(args=args)
    node = ScoutMissionManager()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()

