# Find dependencies
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

# Create executable
add_executable(desktop_app main.cpp)

# Link libraries
target_link_libraries(desktop_app
    PRIVATE
    core
    renderer
    networking
    glfw
    OpenGL::GL
)