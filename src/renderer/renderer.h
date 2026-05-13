#pragma once

#include "shader.h"
#include "mesh.h"
#include "math/transform.h"

// Forward declaration (don't include the header file)
struct GLFWwindow;

namespace renderer {

class Renderer {
public:
  // Initialize the renderer
  bool init();

  // Run the renderer
  void run();

  // Cleanup the renderer
  void cleanup();

private:
  // Window pointer
  GLFWwindow *window = nullptr;

  // Shader
  Shader shader;

  // Mesh
  Mesh mesh;

  // Transform
  math::Transform transform;

  // Render the window
  void render();

  // Update the FPS counter
  void updateFPS();

  // Last time the FPS was updated
  double lastTime = 0.0;

  // Frame count
  int frameCount = 0;
}; // class Renderer

} // namespace renderer