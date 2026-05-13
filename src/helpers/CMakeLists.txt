# Helpers library (file I/O and other small cross-cutting utilities)
add_library(helpers STATIC file.cpp)

# Expose helpers headers to consumers (#include "helpers/file.h")
target_include_directories(helpers PUBLIC
    ${CMAKE_SOURCE_DIR}/src
)
