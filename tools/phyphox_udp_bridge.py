"""
Phyphox UDP bridge.

This script receives sensor data from Phyphox (real device) and sends it to the sensor system.
"""

import requests
import socket
import struct
import time

# Address and port
PORT = 5005
HOST = "127.0.0.1"

# Expected packet length (protocol compliance)
# <BQffff (1 byte + 8 bytes + 4 bytes + 4 bytes + 4 bytes + 4 bytes) = 25 bytes
EXPECTED_DATA_LENGTH = 25

# Phyphox API URL
PHYPHOX_API_URL = "http://192.168.1.99:8080"
ENDPOINT_ATTITUDE = "/get?attW&attX&attY&attZ"

# Create an IPv4 UDP socket for sending data
sender_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

# Loop forever sending data to the socket
i = 0

# Loop forever sending data to the socket
while True:
    # Increment the iteration counter
    i += 1

    try:
        # HTTP GET request to the Phyphox API
        response = requests.get(PHYPHOX_API_URL + ENDPOINT_ATTITUDE, timeout=1.0)

        # Check if the response is successful
        if response.status_code != 200:
            print(f"Error: {response.status_code}")
            time.sleep(1)
            continue

        # Get the attitude data
        attitude = response.json()["buffer"]

        # Get the quaternion data, handling the empty buffer case
        try:
            quaternion_w = attitude["attW"]["buffer"][0]
            quaternion_x = attitude["attZ"]["buffer"][0]
            quaternion_y = attitude["attX"]["buffer"][0]
            quaternion_z = attitude["attY"]["buffer"][0]
        except (KeyError, IndexError):
            print("Received empty buffer from Phyphox.")
            time.sleep(0.1)
            continue

    except requests.exceptions.RequestException as e:
        print(f"Error: {e}")
        time.sleep(1)
        continue

    # Generate quaternion based on the attitude data
    quaternion = {
        "x": quaternion_x,
        "y": quaternion_y,
        "z": quaternion_z,
        "w": quaternion_w,
    }

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
    if len(data) == EXPECTED_DATA_LENGTH:
        sender_socket.sendto(data, (HOST, PORT))
    else:
        print(f"Error: Data length is not {EXPECTED_DATA_LENGTH} bytes")
        time.sleep(1)
        continue

    # Sleep for 16 milliseconds (60 Hz)
    time.sleep(0.016)

    # Print the data every 1000 iterations
    if i % 1000 == 0:
        print(f"Data length: {len(data)}")
        print(f"Sent data to the socket {i} times")
        print("--------------------------------")
