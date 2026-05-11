# Rendering (window, OpenGL, shaders). Replace INTERFACE with STATIC when you add sources.
add_library(renderer INTERFACE)
target_include_directories(renderer INTERFACE
    ${CMAKE_SOURCE_DIR}/src
)
