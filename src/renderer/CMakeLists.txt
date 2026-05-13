# Find dependencies
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

# Renderer implementation (window, OpenGL, etc.)
add_library(renderer STATIC
    renderer.cpp
    mesh.cpp
    shader.cpp
)

# Include directories
target_include_directories(renderer PUBLIC
    ${CMAKE_SOURCE_DIR}/src
)

# Link libraries
target_link_libraries(renderer
    PUBLIC
    glfw
    OpenGL::GL
)

# Compile definitions
target_compile_definitions(renderer PRIVATE
    GL_SILENCE_DEPRECATION
)