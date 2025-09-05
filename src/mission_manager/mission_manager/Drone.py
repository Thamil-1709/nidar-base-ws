#!/usr/bin/env python3
from mavsdk import System
import asyncio

class Drone:
    def __init__(self, name, host, port):
        self.drone_name = "drone_" + str(name)
        self.host = host
        self.port = port
        self.drone = System()
        self.telemetry_data = {}

    def get_drone_status(self):

        return {
            "name": self.drone_name,
            "host": self.host,
            "port": self.port
        }
    
    async def connect(self):
        await self.drone.connect(system_address=f"udp://{self.host}:{self.port}")
        print(f"{self.drone_name} connected to {self.host}:{self.port}")

    async def arm(self):
        print(f"Arming {self.drone_name}...")
        await self.drone.action.arm()
        print(f"{self.drone_name} armed.")

    async def takeoff(self):
        print(f"{self.drone_name} taking off...")
        await self.drone.action.takeoff()
        print(f"{self.drone_name} took off.")

    async def land(self):
        print(f"{self.drone_name} landing...")
        await self.drone.action.land()
        print(f"{self.drone_name} landed.")

    async def return_to_launch(self):
        print(f"{self.drone_name} returning to launch...")
        await self.drone.action.return_to_launch()
        print(f"{self.drone_name} returned to launch.")

    async def telemetry(self):
        async for position in self.drone.telemetry.position():
            print(f"Position: {position.latitude_deg}, {position.longitude_deg}, {position.absolute_altitude_m}m")
            self.telemetry_data = {
                "latitude": position.latitude_deg,
                "longitude": position.longitude_deg,
                "altitude": position.absolute_altitude_m
            }
            break


    async def goto_location(self, latitude, longitude, altitude):
        print(f"{self.drone_name} going to location: lat={latitude}, lon={longitude}, alt={altitude}...")
        await self.drone.action.goto_location(latitude, longitude, altitude, 0)
        print(f"{self.drone_name} reached the location.")


    async def disconnect(self):
        print(f"Disconnecting {self.drone_name}...")
        # No explicit disconnect method in MAVSDK, just stop using the instance
        print(f"{self.drone_name} disconnected.")


if __name__ == "__main__":
    async def main():
        drone = Drone(name=1, host="localhost", port=14445)
        await drone.connect()
        await drone.arm()
        await drone.takeoff()
        await drone.goto_location(47.398039, 8.545572, 10)
        await drone.land()
        await drone.disconnect()

    asyncio.run(main())  