# Engine Notes

## Current stack (as implemented)

- **Language / build**: C++20, CMake 3.16+, `CMAKE_EXPORT_COMPILE_COMMANDS` for IDE tooling.
- **Graphics**: OpenGL 3.3 Core, forward-compatible context (macOS-friendly). GLFW for window, context, and input. GLM for math.
- **Dependencies**: System packages via `find_package` — `glfw3`, `OpenGL`, `glm`. There is no in-tree `FetchContent` yet; document local versions or adopt a pinned strategy when reproducibility matters.

## Runtime layout

- **Entry**: `apps/desktop_app` constructs `renderer::Renderer`, then `init()` → `run()` → `cleanup()`.
- **Frame loop**: `glfwPollEvents`, `update` (delta time from `glfwGetTime`), `render`, `glfwSwapBuffers`; an approximate FPS value is written to the window title about once per second.

## Renderer behavior

- **Window**: 800×600, vsync via `glfwSwapInterval(1)`; framebuffer resize updates the viewport.
- **Shaders**: `shaders/basic.vert` and `shaders/basic.frag`; a single `mat4` uniform named `MVP`.
- **Scene**: A colored unit cube (CPU-defined interleaved position + color vertices) uses `math::Transform` for its model matrix. A ground grid comes from `renderer::geometry::generateGrid(20, 1.0f)` and is drawn with `GL_LINES` and an identity model matrix.
- **Matrices**: `MVP = projection * view * model` with a perspective field of view of 45°, near 0.1, far 100, and aspect ratio from the framebuffer size.

## Coordinate and input conventions

- **World up**: +Y (`glm::vec3(0, 1, 0)` in the camera and in `glm::lookAt`).
- **Camera**: FPS-style movement; default yaw −90°, pitch clamped to roughly ±89°. The view matrix is `glm::lookAt(position, position + front, world_up)`.
- **Keyboard**: W/A/S/D move on the horizontal plane using the camera forward and right vectors; Space moves along world +Y, Left Shift along world −Y.
- **Mouse look**: Applied only while the **right mouse button** is held; cursor deltas update yaw and pitch with a configurable sensitivity.

## Module boundaries

- **`renderer`**: GLFW and GL state, meshes, shader, scene update and draw; links `math`, `camera`, and `helpers`.
- **`camera`**: View matrix and movement from GLFW key codes and mouse deltas (GLM; GLFW included for key constants).
- **`math`**: `Transform` builds the model matrix (translate, Euler rotate X then Y then Z, scale).

## Decisions

- OpenGL is used for direct control and a clear learning path on desktop.
- CMake targets follow `PROJECT_STRUCTURE.md` (`camera`, `math`, `renderer`, and other modules under `src/`).

## Open questions

- Spatial structures and persistence (see `ROADMAP.md` and `src/spatial/`).
- Networking message format and transport (see `src/networking/`).
- How to pin third-party versions (GLFW, GLM) and make installs reproducible (package manager vs `FetchContent`).

## Experiments and operational notes

- `GL_SILENCE_DEPRECATION` reduces deprecation noise on Apple’s OpenGL stack; the code path remains Core Profile.
- Shader paths are relative to the process working directory. Run the binary from the repo root (or place `shaders/` where the executable expects it) until a dedicated asset path is defined.
