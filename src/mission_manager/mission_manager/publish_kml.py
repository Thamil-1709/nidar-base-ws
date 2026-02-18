#!/usr/bin/env python3

import asyncio
import cv2
import math
from ultralytics import YOLO
from mavsdk import System

# ================= CONFIG =================
RTSP_URL = "rtsp://192.168.1.231:8554/1"
MODEL_PATH = "gopi.pt"

MAVSDK_URL = "udp://:14540"

CAMERA_FOV_H = 78.0  # degrees
CAMERA_FOV_V = 64.0  # degrees

PERSON_CLASS_ID = 0  # YOLO person class
CONF_THRESH = 0.4

# =========================================


def compute_victim_gps(bbox, frame_shape, drone):
    """
    bbox: [x1, y1, x2, y2]
    drone: {lat, lon, alt, yaw}
    """
    H, W = frame_shape[:2]
    x1, y1, x2, y2 = bbox

    cx = (x1 + x2) / 2.0
    cy = (y1 + y2) / 2.0

    nx = (cx - W / 2) / (W / 2)
    ny = (cy - H / 2) / (H / 2)

    angle_x = nx * (CAMERA_FOV_H / 2)
    angle_y = ny * (CAMERA_FOV_V / 2)

    lat = drone["lat"]
    lon = drone["lon"]
    alt = drone["alt"]
    yaw = drone["yaw"]

    ground_dist = alt * math.tan(math.radians(angle_y))
    bearing = yaw + angle_x

    R = 6378137.0
    dlat = ground_dist * math.cos(math.radians(bearing)) / R
    dlon = ground_dist * math.sin(math.radians(bearing)) / (R * math.cos(math.radians(lat)))

    return lat + math.degrees(dlat), lon + math.degrees(dlon)


async def get_drone_state(drone):
    async for pos in drone.telemetry.position():
        async for att in drone.telemetry.attitude_euler():
            return {
                "lat": pos.latitude_deg,
                "lon": pos.longitude_deg,
                "alt": pos.relative_altitude_m,
                "yaw": att.yaw_deg
            }


async def main():
    print("[INFO] Loading YOLO model...")
    model = YOLO(MODEL_PATH)

    print("[INFO] Opening RTSP stream...")
    cap = cv2.VideoCapture(RTSP_URL)

    print("[INFO] Connecting to drone via MAVSDK...")
    drone = System()
    await drone.connect(system_address=MAVSDK_URL)

    async for state in drone.core.connection_state():
        if state.is_connected:
            print("[OK] Drone connected")
            break

    victim_sent = False

    while True:
        ret, frame = cap.read()
        if not ret:
            continue

        results = model(frame, conf=CONF_THRESH, classes=[PERSON_CLASS_ID], verbose=False)

        if not victim_sent and len(results[0].boxes) > 0:
            bbox = results[0].boxes[0].xyxy[0].cpu().numpy()

            drone_state = await get_drone_state(drone)
            vlat, vlon = compute_victim_gps(bbox, frame.shape, drone_state)

            msg = f"VICTIM DETECTED @ {vlat:.6f}, {vlon:.6f}"
            print("[RESULT]", msg)

            # Send to GCS (QGC message panel)
            await drone.telemetry.text_status(msg)

            victim_sent = True  # 🔒 single-shot only

        annotated = results[0].plot()
        cv2.imshow("YOLO Victim Detection", annotated)

        if cv2.waitKey(1) == 27:  # ESC
            break

    cap.release()
    cv2.destroyAllWindows()


if __name__ == "__main__":
    asyncio.run(main())
