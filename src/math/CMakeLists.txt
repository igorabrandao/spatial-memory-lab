# Math module (vectors, matrices, quaternions). Replace INTERFACE with STATIC
# and list sources once you add implementation files.
add_library(math INTERFACE)
target_include_directories(math INTERFACE
    ${CMAKE_SOURCE_DIR}/src
)
