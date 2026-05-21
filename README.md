# Spatial Memory Lab

A low-level experimental system for spatial computing, combining computer vision, sensor data, and 3D rendering using C++.

## Demo

**[Watch on YouTube](https://youtu.be/SNvDGKU2MGI)** — desktop app driven by live phone orientation (Phyphox → UDP bridge).

## 🚀 Overview

Spatial Memory Lab is a modular engine designed to:
- perceive physical space
- track motion using sensors and vision
- reconstruct environments in 3D
- build a persistent spatial memory

This project focuses on **deep technical learning**, not just product delivery.

## 🧠 Core Concepts

- Spatial Computing
- Computer Vision
- 3D Graphics
- Sensor Fusion
- Real-time Systems

## ⚙️ Tech Stack

- C++
- CMake
- OpenGL
- GLFW
- GLM
- Dear ImGui
- OpenCV (planned)

## 🎯 First Milestone

Move a 3D cube using Android gyroscope data.

## 📈 Roadmap

See ROADMAP.md

## 🤖 AI Usage

AI is used as:
- assistant
- reviewer
- explainer

NOT as:
- full system generator

## 🧪 Philosophy

- Learn by building
- Visualize everything
- Prefer clarity over abstraction
- Build systems, not scripts

## 🛠 Getting Started

### Prerequisites

- A C++20 compiler (Clang, AppleClang or GCC)
- CMake ≥ 3.16
- GLFW 3 and an OpenGL implementation available on the system
  (on macOS with Homebrew: `brew install cmake glfw`)

### Clone

```bash
git clone <repo> spatial-memory-lab
cd spatial-memory-lab
```

### Build and run with the Makefile

The repository ships a convenience `Makefile` that wraps the common CMake
commands. `cmake` remains the source of truth (see `CMakeLists.txt`); the
`Makefile` only saves a few keystrokes.

```bash
make help              # list available targets and variables
make build             # configure (if needed) and compile
make run               # build and run the default app (apps/desktop_app)
make run APP=<name>    # build and run apps/<name>/<name>
make rebuild           # clean + build
make distclean         # remove the entire build/ directory
```

Useful variables (override on the command line):

| Variable           | Default       | Purpose                                       |
| ------------------ | ------------- | --------------------------------------------- |
| `APP`              | `desktop_app` | Which executable under `apps/` to run         |
| `BUILD_DIR`        | `build`       | Output directory for the CMake build tree     |
| `CMAKE_BUILD_TYPE` | `Debug`       | `Debug`, `Release`, `RelWithDebInfo`, …       |
| `CMAKE_GENERATOR`  | *(system)*    | e.g. `Ninja`, `Xcode`                         |
| `JOBS`             | *(all cores)* | Forwarded as `--parallel` to `cmake --build`  |
| `CMAKE_FLAGS`      | *(empty)*     | Extra flags passed at configure time          |

Examples:

```bash
make build CMAKE_BUILD_TYPE=Release JOBS=8
make run APP=desktop_app
make configure CMAKE_GENERATOR=Ninja
```

### Build and run with raw CMake

If you prefer to drive CMake directly:

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build --parallel
./build/apps/desktop_app/desktop_app
```

## Python sensor tools

The `tools/` directory holds small **UDP senders** that feed the desktop app with orientation samples. They speak the same binary format as `SensorPacket` in `src/networking/SensorPacket.h` (25 bytes, little-endian: version, timestamp, `qx qy qz qw`) and target **127.0.0.1:5005**, which matches the default port used by `apps/desktop_app`.

| Script | Purpose |
| --- | --- |
| `tools/fake_sensor_sender.py` | Generates a smooth synthetic rotation (~60 Hz) for testing without a phone. |
| `tools/phyphox_udp_bridge.py` | Polls [Phyphox](https://phyphox.org/) on your phone over HTTP and forwards real attitude quaternions to the app. |

### Prerequisites

- **Python 3** (stdlib only for the fake sender).
- For the Phyphox bridge: `pip install requests` (or any environment where `import requests` works).

### Typical workflow

1. **Start the desktop app** (it binds UDP port 5005 and listens for packets):

   ```bash
   make run
   # or: ./build/apps/desktop_app/desktop_app
   ```

2. **In a second terminal**, run **one** sender script (do not run both at once on the same port).

### Fake sender (no phone)

Use this to verify the render loop, UDP receiver, and cube motion without hardware:

```bash
python3 tools/fake_sensor_sender.py
```

The script rotates a quaternion around the Y axis at ~60 Hz. You should see periodic log lines every ~16 s and the cube moving in the window.

### Phyphox bridge (real phone sensors)

[Phyphox](https://phyphox.org/) is a free app (iOS / Android) that exposes the device IMU and fused orientation. This project uses Phyphox as a **quick stand-in** for a native Android stream while the milestone is still “move a cube from phone gyro data.”

**On the phone**

1. Install Phyphox and open an experiment that exposes **attitude** (orientation quaternion), or use the built-in remote sensor access.
2. Enable **remote access** in Phyphox (same Wi‑Fi as your computer). Note the URL shown in the app, e.g. `http://192.168.1.42:8080`.
3. Keep the experiment running so attitude buffers stay populated.

**On the computer**

1. Edit `PHYPHOX_API_URL` at the top of `tools/phyphox_udp_bridge.py` to match your phone’s IP and port (not the placeholder `192.168.1.99`).
2. Run the bridge:

   ```bash
   python3 tools/phyphox_udp_bridge.py
   ```

The script polls Phyphox’s HTTP API (`/get?attW&attX&attY&attZ`), maps the attitude fields into the lab’s quaternion layout, packs a `SensorPacket`, and sends UDP to localhost. Rotate the phone and confirm the cube follows.

**Troubleshooting**

- Connection errors: confirm phone and laptop are on the same network, firewall allows LAN traffic, and the IP in the script matches Phyphox’s remote screen.
- “Received empty buffer”: start the attitude experiment in Phyphox and wait until samples appear before relying on the bridge.
- Nothing moves in the app: ensure `desktop_app` is running first and only one script is bound to port 5005.

Wire format and coordinate notes: `docs/ENGINE_NOTES.md` (Phase 2: Sensor streaming).

## 📄 License

MIT License
