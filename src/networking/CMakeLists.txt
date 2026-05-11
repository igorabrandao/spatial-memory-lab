# Networking (e.g. UDP). Replace INTERFACE with STATIC when you add .cpp files.
add_library(networking INTERFACE)
target_include_directories(networking INTERFACE
    ${CMAKE_SOURCE_DIR}/src
)
