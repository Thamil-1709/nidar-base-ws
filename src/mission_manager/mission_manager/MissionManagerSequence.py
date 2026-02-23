#!/usr/bin/env python3

import rclpy
import json
import threading
from datetime import datetime

from rclpy.node import Node
from rclpy.action import ActionClient
from rclpy.executors import MultiThreadedExecutor
from rclpy.callback_groups import ReentrantCallbackGroup

from std_msgs.msg import String
from geographic_msgs.msg import GeoPoint

from mission_interfaces.srv import StartMission
from mission_interfaces.srv import ConfirmPayloadLoaded   # Gate 1
from mission_interfaces.srv import ConfirmNextBatch       # Gate 2
from mission_interfaces.action import ScoutActionTrigger
from mission_interfaces.action import MultiDeliveryActionTrigger
from mission_interfaces.msg import DeliveryWaypoint


# ================= CONFIG =================
DEFAULT_DELIVERY_ALT_M   = 10.0   # Altitude if victim GeoPoint alt is 0
BATCH_WAIT_SEC           = 5.0    # Window to accumulate victims into one batch
MAX_BATCH_SIZE           = 6      # Max waypoints per flight (servo range 0–6)
CONFIRMATION_TIMEOUT_SEC = 120.0  # Seconds to wait for operator confirmation


# ================= SERVICE INTERFACE REFERENCE =================
#
# ConfirmPayloadLoaded.srv
# ─────────────────────────
#   uint8  batch_size    # (informational) number of payloads to load
#   bool   confirmed     # operator sets True when payloads are on board
#   ---
#   bool   confirmed
#   string message
#
# ConfirmNextBatch.srv
# ─────────────────────
#   uint8  queued_victims   # (informational) how many victims still queued
#   uint8  next_batch_size  # (informational) how many will fly next
#   bool   confirmed        # operator sets True to dispatch next batch
#   bool   clear_queue      # operator sets True to discard remaining victims
#   ---
#   bool   confirmed
#   string message


class MissionManager(Node):
    """
    Orchestrates scout and multi-delivery drones.

    Two human-confirmation gates are inserted into the delivery pipeline:

    ┌─────────────────────────────────────────────────────────────────┐
    │  GATE 1  /delivery/confirm_payload_loaded                       │
    │  Triggered : after a batch is built, BEFORE takeoff             │
    │  Operator  : physically loads payloads, then calls service      │
    │              with confirmed=True                                │
    │  On timeout: batch is re-queued, system returns to Standby      │
    └─────────────────────────────────────────────────────────────────┘

    ┌─────────────────────────────────────────────────────────────────┐
    │  GATE 2  /delivery/confirm_next_batch                           │
    │  Triggered : after drone lands AND more victims are queued      │
    │  Operator  : swaps batteries / checks airframe, then calls      │
    │              service with confirmed=True                        │
    │              OR calls with clear_queue=True to discard queue    │
    │  On timeout: queue is paused; operator must call service again  │
    └─────────────────────────────────────────────────────────────────┘
    """

    def __init__(self):
        super().__init__('mission_manager')
        self.get_logger().info("Mission Manager started")

        self._cb_group = ReentrantCallbackGroup()

        # ---------- mission state ----------
        self.victim_queue             = []
        self.delivery_busy            = False
        self.scout_running            = False
        self.current_scout_goal       = None
        self.victim_detected_count    = 0
        self.delivery_completed_count = 0
        self._batch_dispatch_timer    = None

        # ---------- Gate 1: payload loaded ----------
        self._payload_confirmed = threading.Event()

        # ---------- Gate 2: next batch ready ----------
        self._next_batch_confirmed  = threading.Event()
        self._clear_queue_requested = False

        # ---------- publishers ----------
        self.state_pub    = self.create_publisher(String, '/mission/state',               10)
        self.victim_pub   = self.create_publisher(String, '/mission/victim_count',        10)
        self.delivery_pub = self.create_publisher(String, '/mission/delivery_count',      10)
        self.alert_pub    = self.create_publisher(String, '/mission/alerts',              10)
        self.waypoint_pub = self.create_publisher(String, '/mission/delivery_waypoints',  10)

        self._publish_state("Standby")

        # ---------- services this node EXPOSES ----------
        self.create_service(
            StartMission, 'start_mission',
            self.start_mission_callback,
            callback_group=self._cb_group
        )

        # Gate 1 service
        self.create_service(
            ConfirmPayloadLoaded,
            '/delivery/confirm_payload_loaded',
            self.confirm_payload_loaded_callback,
            callback_group=self._cb_group
        )

        # Gate 2 service
        self.create_service(
            ConfirmNextBatch,
            '/delivery/confirm_next_batch',
            self.confirm_next_batch_callback,
            callback_group=self._cb_group
        )

        # ---------- subscriptions ----------
        self.create_subscription(
            GeoPoint, '/scout/victim_detected', self.victim_callback, 10
        )
        self.create_subscription(
            String, '/scout_drone/state', self.scout_state_callback, 10
        )
        self.create_subscription(
            String, '/delivery/state', self.delivery_state_callback, 10
        )

        # ---------- action clients ----------
        self.scout_client = ActionClient(
            self, ScoutActionTrigger, 'start_scan',
            callback_group=self._cb_group
        )
        self.delivery_client = ActionClient(
            self, MultiDeliveryActionTrigger, 'start_multi_delivery',
            callback_group=self._cb_group
        )

        self.get_logger().info("Mission Manager ready")

    # ==============================================================
    # HELPERS
    # ==============================================================

    def _publish_state(self, state: str):
        self.state_pub.publish(String(data=state))
        self.get_logger().info(f"[State] {state}")

    def publish_alert(self, alert_type: str, severity: str, message: str,
                      latitude=None, longitude=None):
        alert = {
            "type":      alert_type,
            "severity":  severity,
            "message":   message,
            "latitude":  latitude,
            "longitude": longitude,
            "timestamp": datetime.now().strftime("%H:%M:%S")
        }
        self.alert_pub.publish(String(data=json.dumps(alert)))

    # ==============================================================
    # GATE 1 SERVICE — /delivery/confirm_payload_loaded
    # ==============================================================

    def confirm_payload_loaded_callback(self, request, response):
        """
        Operator calls this service with confirmed=True once all payloads
        for the current batch have been physically loaded onto the drone.
        This unblocks _dispatch_with_confirmation() so the drone can take off.
        """
        self.get_logger().info(
            f"[GATE 1] confirm_payload_loaded called — "
            f"batch_size={request.batch_size} confirmed={request.confirmed}"
        )

        if request.confirmed:
            self._payload_confirmed.set()
            response.confirmed = True
            response.message   = (
                f"Payload confirmed for {request.batch_size} item(s) — "
                f"drone will take off now"
            )
            self.get_logger().info("[ GATE 1 UNLOCKED ] Payloads confirmed — proceeding to takeoff")
            self.publish_alert(
                "PAYLOAD_CONFIRMED", "LOW",
                f"Operator confirmed {request.batch_size} payload(s) loaded — taking off"
            )
        else:
            response.confirmed = False
            response.message   = (
                "Confirmation not received. "
                "Call again with confirmed=True when payloads are loaded."
            )
            self.get_logger().warn(
                "[GATE 1] Called with confirmed=False — still waiting for payload load"
            )

        return response

    # ==============================================================
    # GATE 2 SERVICE — /delivery/confirm_next_batch
    # ==============================================================

    def confirm_next_batch_callback(self, request, response):
        """
        Operator calls this service after the drone lands.
        - confirmed=True  → dispatch next batch (triggers Gate 1 again)
        - clear_queue=True → discard remaining victims, return to standby
        Both flags can be set at once to clear queue without dispatching.
        """
        self.get_logger().info(
            f"[GATE 2] confirm_next_batch called — "
            f"confirmed={request.confirmed} clear_queue={request.clear_queue} "
            f"queued={request.queued_victims} next_batch={request.next_batch_size}"
        )

        # Handle queue clear regardless of confirmed flag
        if request.clear_queue:
            cleared = len(self.victim_queue)
            self.victim_queue.clear()
            self._clear_queue_requested = True
            self.get_logger().warn(
                f"[GATE 2] Operator cleared victim queue — {cleared} victim(s) discarded"
            )
            self.publish_alert(
                "QUEUE_CLEARED", "MEDIUM",
                f"Operator cleared {cleared} queued victim(s)"
            )
            response.confirmed = True
            response.message   = f"Queue cleared — {cleared} victim(s) discarded. Returning to standby."
            self._next_batch_confirmed.set()
            return response

        if request.confirmed:
            self._next_batch_confirmed.set()
            response.confirmed = True
            response.message   = (
                f"Drone confirmed ready — dispatching next batch of "
                f"{request.next_batch_size} waypoint(s)"
            )
            self.get_logger().info("[ GATE 2 UNLOCKED ] Drone ready — next batch will be dispatched")
            self.publish_alert(
                "NEXT_BATCH_CONFIRMED", "LOW",
                f"Operator confirmed drone ready — next batch of "
                f"{request.next_batch_size} dispatching now"
            )
        else:
            response.confirmed = False
            response.message   = (
                f"{request.queued_victims} victim(s) still queued. "
                "Call again with confirmed=True when drone is ready, "
                "or set clear_queue=True to discard the queue."
            )
            self.get_logger().warn(
                "[GATE 2] Called with confirmed=False — still waiting for operator"
            )

        return response

    # ==============================================================
    # START MISSION
    # ==============================================================

    def start_mission_callback(self, request, response):
        if self.scout_running:
            self.get_logger().warn("Scout already running — rejecting")
            response.accepted = False
            return response

        if not request.waypoints:
            self.get_logger().warn("No waypoints — rejecting")
            response.accepted = False
            return response

        self.get_logger().info(
            f"Starting scout with {len(request.waypoints)} waypoint(s)"
        )

        self.scout_client.wait_for_server()
        goal_msg           = ScoutActionTrigger.Goal()
        goal_msg.waypoints = request.waypoints

        send_future = self.scout_client.send_goal_async(goal_msg)
        send_future.add_done_callback(self.scout_goal_response_callback)

        self.scout_running = True
        self._publish_state("Scout active")
        self.publish_alert("MISSION_STARTED", "LOW", "Scout mission initiated")

        response.accepted = True
        return response

    # ==============================================================
    # SCOUT CALLBACKS
    # ==============================================================

    def scout_goal_response_callback(self, future):
        goal_handle = future.result()
        if not goal_handle.accepted:
            self.get_logger().error("Scout goal rejected")
            self.publish_alert("MISSION_REJECTED", "HIGH", "Scout mission rejected")
            self.scout_running = False
            self._publish_state("Standby")
            return

        self.current_scout_goal = goal_handle
        goal_handle.get_result_async().add_done_callback(self.scout_result_callback)

    def scout_result_callback(self, future):
        self.get_logger().info("Scout mission finished")
        self.publish_alert("MISSION_COMPLETE", "MEDIUM", "Scout mission completed")
        self.scout_running = False

        if self.victim_queue and not self.delivery_busy:
            self.get_logger().info(
                f"Scout done — {len(self.victim_queue)} victim(s) queued, "
                f"starting batch dispatch"
            )
            self._schedule_batch_dispatch()

        if not self.delivery_busy:
            self._publish_state("Standby")

    def scout_state_callback(self, msg: String):
        if msg.data == "Returning to Launch":
            self.publish_alert("MISSION_RTL", "LOW", "Scout returning to launch")

    def delivery_state_callback(self, msg: String):
        self.get_logger().debug(f"Delivery state: {msg.data}")

    # ==============================================================
    # VICTIM DETECTION
    # ==============================================================

    def victim_callback(self, msg: GeoPoint):
        self.get_logger().info(
            f"Victim detected at ({msg.latitude:.6f}, {msg.longitude:.6f})"
        )
        self.victim_queue.append(msg)
        self.victim_detected_count += 1
        self.victim_pub.publish(String(data=str(self.victim_detected_count)))
        self.publish_alert(
            "VICTIM_DETECTED", "HIGH",
            f"Victim #{self.victim_detected_count} detected",
            msg.latitude, msg.longitude
        )

        if not self.delivery_busy:
            self._schedule_batch_dispatch()

    def _schedule_batch_dispatch(self):
        """Start or reset the batch accumulation window."""
        if len(self.victim_queue) >= MAX_BATCH_SIZE:
            self.get_logger().info("Batch full — dispatching immediately")
            if self._batch_dispatch_timer:
                self._batch_dispatch_timer.cancel()
                self._batch_dispatch_timer = None
            threading.Thread(
                target=self._dispatch_with_confirmation, daemon=True
            ).start()
            return

        if self._batch_dispatch_timer:
            self._batch_dispatch_timer.cancel()

        self._batch_dispatch_timer = self.create_timer(
            BATCH_WAIT_SEC, self._batch_timer_callback
        )
        self.get_logger().info(
            f"Batch window reset — {len(self.victim_queue)} victim(s) queued, "
            f"dispatching in {BATCH_WAIT_SEC}s unless more arrive"
        )

    def _batch_timer_callback(self):
        if self._batch_dispatch_timer:
            self._batch_dispatch_timer.cancel()
            self._batch_dispatch_timer = None

        if self.victim_queue and not self.delivery_busy:
            threading.Thread(
                target=self._dispatch_with_confirmation, daemon=True
            ).start()

    # ==============================================================
    # GATE 1 FLOW — build batch → wait for payload confirm → dispatch
    # ==============================================================

    def _dispatch_with_confirmation(self):
        """
        Background thread — blocks on Gate 1 before sending the goal.

        Step 1 : Pop up to MAX_BATCH_SIZE victims from queue
        Step 2 : Alert operator to load payloads
        Step 3 : Block on /delivery/confirm_payload_loaded  ← GATE 1
        Step 4 : Send MultiDeliveryActionTrigger goal
        """
        if self.delivery_busy or not self.victim_queue:
            return

        # ---- Step 1: Build batch ----
        batch = []
        while self.victim_queue and len(batch) < MAX_BATCH_SIZE:
            batch.append(self.victim_queue.pop(0))

        batch_size = len(batch)
        self.get_logger().info(
            f"Batch of {batch_size} built — waiting for GATE 1 (payload load)"
        )

        # ---- Step 2: Alert operator ----
        self._payload_confirmed.clear()
        self._publish_state("Awaiting payload load confirmation")

        self.publish_alert(
            "PAYLOAD_LOAD_REQUIRED", "HIGH",
            f"ACTION REQUIRED: Load {batch_size} payload(s) onto the drone. "
            f"Then call: ros2 service call /delivery/confirm_payload_loaded "
            f"mission_interfaces/srv/ConfirmPayloadLoaded "
            f"\"{{batch_size: {batch_size}, confirmed: true}}\""
        )

        self.get_logger().warn(
            f"[ GATE 1 WAITING ] Load {batch_size} payload(s) then call "
            f"/delivery/confirm_payload_loaded "
            f"(timeout={CONFIRMATION_TIMEOUT_SEC}s)"
        )

        # ---- Step 3: Block until confirmed or timeout ----
        confirmed = self._payload_confirmed.wait(timeout=CONFIRMATION_TIMEOUT_SEC)

        if not confirmed:
            self.get_logger().error(
                f"[ GATE 1 TIMEOUT ] No payload confirmation after "
                f"{CONFIRMATION_TIMEOUT_SEC}s — re-queuing {batch_size} victim(s)"
            )
            self.publish_alert(
                "PAYLOAD_TIMEOUT", "HIGH",
                f"Payload confirmation timed out — "
                f"{batch_size} victim(s) re-queued. "
                f"Call /delivery/confirm_payload_loaded to retry."
            )
            # Re-insert at front of queue so order is preserved
            self.victim_queue = batch + self.victim_queue
            self._publish_state("Standby — payload timeout")
            return

        # ---- Step 4: Send goal ----
        self.get_logger().info("[ GATE 1 PASSED ] Sending delivery goal")
        self._send_delivery_goal(batch)

    def _send_delivery_goal(self, batch: list):
        """Convert batch to waypoints and fire the action goal."""
        waypoints = []
        for servo_idx, victim in enumerate(batch):
            wp             = DeliveryWaypoint()
            wp.latitude    = victim.latitude
            wp.longitude   = victim.longitude
            wp.altitude    = victim.altitude if victim.altitude > 0.0 \
                             else DEFAULT_DELIVERY_ALT_M
            wp.servo_index = servo_idx
            waypoints.append(wp)

            self.publish_alert(
                "DELIVERY_WAYPOINT_ADDED", "LOW",
                f"Waypoint {servo_idx + 1}/{len(batch)} — servo {servo_idx}",
                victim.latitude, victim.longitude
            )

        self.waypoint_pub.publish(String(data=json.dumps([
            {"lat": w.latitude, "lon": w.longitude,
             "alt": w.altitude,  "servo": w.servo_index}
            for w in waypoints
        ])))

        self.delivery_client.wait_for_server()
        goal_msg           = MultiDeliveryActionTrigger.Goal()
        goal_msg.waypoints = waypoints

        send_future = self.delivery_client.send_goal_async(
            goal_msg,
            feedback_callback=self.delivery_feedback_callback
        )
        send_future.add_done_callback(self.delivery_goal_response_callback)

        self.delivery_busy = True
        self._publish_state("Delivery active")
        self.publish_alert(
            "DELIVERY_DISPATCHED", "MEDIUM",
            f"Delivery drone dispatched to {len(batch)} location(s)"
        )

    # ==============================================================
    # DELIVERY ACTION CALLBACKS
    # ==============================================================

    def delivery_goal_response_callback(self, future):
        goal_handle = future.result()
        if not goal_handle.accepted:
            self.get_logger().error("Delivery goal rejected")
            self.delivery_busy = False
            self.publish_alert("DELIVERY_REJECTED", "HIGH", "Delivery goal rejected")
            if not self.scout_running:
                self._publish_state("Standby")
            return

        self.get_logger().info("Delivery goal accepted")
        goal_handle.get_result_async().add_done_callback(self.delivery_result_callback)

    def delivery_feedback_callback(self, feedback_msg):
        fb = feedback_msg.feedback
        self.get_logger().debug(
            f"Delivery WP {fb.waypoint_index + 1}/{fb.total_waypoints} "
            f"pos=({fb.current_lat:.5f}, {fb.current_lon:.5f}) "
            f"alt={fb.current_alt:.1f}m dist={fb.distance_to_next:.1f}m"
        )

    def delivery_result_callback(self, future):
        """
        Called when the delivery drone has landed.

        Critical ordering:
          1. delivery_busy = False       (unlock)
          2. Log / publish result
          3. Check victim_queue → if non-empty, enter Gate 2 flow
        """
        result = future.result().result

        # ---- Step 1: Unlock ----
        self.delivery_busy = False

        # ---- Step 2: Result ----
        if result.success == 1.0:
            self.delivery_completed_count += 1
            self.delivery_pub.publish(String(data=str(self.delivery_completed_count)))
            self.get_logger().info(
                f"Delivery #{self.delivery_completed_count} completed successfully"
            )
            self.publish_alert(
                "DELIVERY_COMPLETE", "LOW",
                f"Delivery mission #{self.delivery_completed_count} completed"
            )
        elif result.success == 0.0:
            self.get_logger().warn("Delivery cancelled")
            self.publish_alert("DELIVERY_CANCELLED", "MEDIUM", "Delivery cancelled")
        else:
            self.get_logger().error("Delivery failed/aborted")
            self.publish_alert("DELIVERY_FAILED", "HIGH", "Delivery failed")

        # ---- Step 3: Gate 2 check ----
        if self.victim_queue:
            threading.Thread(
                target=self._wait_for_next_batch_confirmation, daemon=True
            ).start()
        elif not self.scout_running:
            self._publish_state("Standby")

    # ==============================================================
    # GATE 2 FLOW — wait for operator ready → dispatch next batch
    # ==============================================================

    def _wait_for_next_batch_confirmation(self):
        """
        Background thread — blocks on Gate 2 after drone lands.

        Step 1 : Publish alert asking operator to confirm drone is ready
        Step 2 : Block on /delivery/confirm_next_batch  ← GATE 2
        Step 3a: If clear_queue → discard victims, return to standby
        Step 3b: If confirmed  → kick off _dispatch_with_confirmation
                                  (which triggers Gate 1 again)
        Step 3c: If timeout    → pause queue, require manual call to resume
        """
        queued     = len(self.victim_queue)
        next_size  = min(queued, MAX_BATCH_SIZE)

        # ---- Step 1: Alert ----
        self._next_batch_confirmed.clear()
        self._clear_queue_requested = False

        self._publish_state("Awaiting next batch confirmation")

        self.publish_alert(
            "NEXT_BATCH_PENDING", "MEDIUM",
            f"ACTION REQUIRED: Drone has landed. {queued} victim(s) queued. "
            f"Swap batteries and check airframe, then call: "
            f"ros2 service call /delivery/confirm_next_batch "
            f"mission_interfaces/srv/ConfirmNextBatch "
            f"\"{{queued_victims: {queued}, next_batch_size: {next_size}, "
            f"confirmed: true, clear_queue: false}}\""
        )

        self.get_logger().warn(
            f"[ GATE 2 WAITING ] {queued} victim(s) queued. "
            f"Swap batteries then call /delivery/confirm_next_batch "
            f"(timeout={CONFIRMATION_TIMEOUT_SEC}s)"
        )

        # ---- Step 2: Block ----
        confirmed = self._next_batch_confirmed.wait(timeout=CONFIRMATION_TIMEOUT_SEC)

        # ---- Step 3: Handle result ----
        if not confirmed:
            self.get_logger().error(
                f"[ GATE 2 TIMEOUT ] No confirmation after "
                f"{CONFIRMATION_TIMEOUT_SEC}s — "
                f"{len(self.victim_queue)} victim(s) remain queued but paused"
            )
            self.publish_alert(
                "NEXT_BATCH_TIMEOUT", "HIGH",
                f"Next-batch confirmation timed out — "
                f"{len(self.victim_queue)} victim(s) paused. "
                f"Call /delivery/confirm_next_batch to resume."
            )
            self._publish_state("Standby — queue paused")
            return

        if self._clear_queue_requested:
            self.get_logger().info(
                "[GATE 2] Queue cleared by operator — returning to standby"
            )
            self._publish_state("Standby")
            return

        # Gate 2 passed — next batch dispatch (Gate 1 will fire again there)
        self.get_logger().info(
            "[GATE 2 PASSED] Operator confirmed — dispatching next batch"
        )
        threading.Thread(
            target=self._dispatch_with_confirmation, daemon=True
        ).start()


# ==============================================================
# ENTRY POINT
# ==============================================================

def main(args=None):
    rclpy.init(args=args)
    node = MissionManager()
    executor = MultiThreadedExecutor()

    try:
        rclpy.spin(node, executor)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()