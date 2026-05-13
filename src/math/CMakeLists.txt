# -------------------------------------------------------------
# Math module
# -------------------------------------------------------------

# Add the math library
add_library(math STATIC
    transform.cpp
)

# Include directories
target_include_directories(math PUBLIC
    ${CMAKE_SOURCE_DIR}/src
)

# Find the glm library
find_package(glm REQUIRED)

# Link the glm library
target_link_libraries(math PUBLIC glm::glm)

# Compile definitions
target_compile_definitions(math PRIVATE
    GL_SILENCE_DEPRECATION
)