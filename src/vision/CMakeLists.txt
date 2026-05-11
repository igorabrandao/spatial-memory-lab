# Computer vision. Replace INTERFACE with STATIC when you add sources.
add_library(vision INTERFACE)
target_include_directories(vision INTERFACE
    ${CMAKE_SOURCE_DIR}/src
)
