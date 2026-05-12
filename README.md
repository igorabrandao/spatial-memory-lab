# Spatial Memory Lab

A low-level experimental system for spatial computing, combining computer vision, sensor data, and 3D rendering using C++.

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

## 📄 License

MIT License
