cmake_minimum_required(VERSION 3.16)

project(SpatialMemoryLab LANGUAGES CXX)

# -----------------------------
# C++ Standard
# -----------------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# -----------------------------
# Compiler warnings (optional, but recommended)
# -----------------------------
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang|AppleClang|GNU")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# -----------------------------
# Third-party (future)
# -----------------------------
# add_subdirectory(libs)

# -----------------------------
# Source modules
# -----------------------------
add_subdirectory(src)

# -----------------------------
# Applications
# -----------------------------
add_subdirectory(apps)