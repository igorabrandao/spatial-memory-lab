# -------------------------------------------------------------
# Camera module
# -------------------------------------------------------------

# Find the dependencies
find_package(glm REQUIRED)

# Add the camera library
add_library(camera STATIC
    camera.cpp
)

# Include directories
target_include_directories(camera PUBLIC
    ${CMAKE_SOURCE_DIR}/src
)

# Link the dependencies
target_link_libraries(camera PUBLIC glm::glm)

# Compile definitions
target_compile_definitions(camera PRIVATE
    GL_SILENCE_DEPRECATION
)