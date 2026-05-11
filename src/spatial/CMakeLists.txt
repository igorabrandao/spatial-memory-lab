# Spatial mapping and memory. Replace INTERFACE with STATIC when you add sources.
add_library(spatial INTERFACE)
target_include_directories(spatial INTERFACE
    ${CMAKE_SOURCE_DIR}/src
)
