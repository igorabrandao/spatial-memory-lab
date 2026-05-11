# Add the executable
add_executable(desktop_app main.cpp)

# Link the executable to the core library
target_link_libraries(desktop_app PRIVATE core)