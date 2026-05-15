# -------------------------------------------------------------
# Networking module
# -------------------------------------------------------------

# Find the required libraries
find_package(Threads REQUIRED)

# Add the networking library
add_library(networking STATIC UdpReceiver.cpp)

# Include directories
target_include_directories(networking PUBLIC
    ${CMAKE_SOURCE_DIR}/src
)

# Link the required libraries
target_link_libraries(networking PUBLIC
    Threads::Threads
)