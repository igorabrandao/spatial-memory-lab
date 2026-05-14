#pragma once

#include "shader.h"
#include "mesh.h"
#include "math/transform.h"
#include "camera/camera.h"

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

  // Meshes
  Mesh cubeMesh;
  Mesh gridMesh;

  // Transform
  math::Transform transform;

  // Camera
  camera::Camera camera;

  // Update the renderer
  void update();

  // Render the window
  void render();

  // Update the FPS counter
  void updateFPS();

  // Process the input
  void processInput(float deltaTime);

  // Last time the FPS was updated
  double lastTime = 0.0;

  // Frame count
  int frameCount = 0;
}; // class Renderer

} // namespace renderer