# Sensor input / IMU parsing. Replace INTERFACE with STATIC when you add sources.
add_library(sensors INTERFACE)
target_include_directories(sensors INTERFACE
    ${CMAKE_SOURCE_DIR}/src
)
