# -------------------------------------------------------------
# Sensors module
# -------------------------------------------------------------

# Find the required libraries
find_package(glm REQUIRED)

# Add the sensors library
add_library(sensors STATIC SensorSystem.cpp)

# Expose sensors headers to consumers
target_include_directories(sensors PUBLIC
    ${CMAKE_SOURCE_DIR}/src
)

# Link the glm library
target_link_libraries(sensors PUBLIC glm::glm)

# Compile definitions
target_compile_definitions(sensors PRIVATE
    GL_SILENCE_DEPRECATION
)