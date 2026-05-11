# Add the core library
add_library(core STATIC core.cpp)

# Expose core headers to consumers
target_include_directories(core PUBLIC
    ${CMAKE_SOURCE_DIR}/src
)