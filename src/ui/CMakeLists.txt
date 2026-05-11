# UI (e.g. Dear ImGui). Replace INTERFACE with STATIC when you add sources.
add_library(ui INTERFACE)
target_include_directories(ui INTERFACE
    ${CMAKE_SOURCE_DIR}/src
)
