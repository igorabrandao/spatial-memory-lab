"""
Fake sensor sender.

This script sends fake sensor data to the sensor system.
"""

import socket
import struct
import time

# Address and port
PORT = 5005
HOST = "127.0.0.1"

# Create an IPv4 UDP socket for sending data
sender_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Loop forever sending data to the socket
i = 0
while True:
    # Generate identity quaternion
    quaternion = {"x": 0.0, "y": 0.0, "z": 0.0, "w": 1.0}

    # Generate timestamp in nanoseconds
    timestamp = time.time_ns()

    # Generate the version byte
    version = 1

    # Pack data into a struct
    data = struct.pack(
        "<BQffff",
        version,
        timestamp,
        quaternion["x"],
        quaternion["y"],
        quaternion["z"],
        quaternion["w"],
    )

    # Send data to the socket
    sender_socket.sendto(data, (HOST, PORT))

    # Sleep for 16 milliseconds (60 Hz)
    time.sleep(0.016)

    # Increment the iteration counter
    i += 1

    # Print the data every 1000 iterations
    if i % 1000 == 0:
        print(f"Data length: {len(data)}")
        print(f"Sent data to the socket {i} times")
