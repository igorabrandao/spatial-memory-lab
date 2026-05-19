#pragma once

#include "camera/camera.h"
#include "math/transform.h"
#include "mesh.h"
#include "sensors/SensorSystem.h"
#include "shader.h"

// Forward declaration (don't include the header file)
struct GLFWwindow;

// Forward declaration (don't include the header file)
class SensorSystem;

namespace renderer {

class Renderer {
public:
  // Constructor
  Renderer(sensors::SensorSystem &sensorSystem);

  // Destructor
  ~Renderer();

  // Initialize the renderer
  bool init();

  // Run the renderer
  void run();

  // Cleanup the renderer
  void cleanup();

private:
  // Update the renderer
  void update();

  // Render the window
  void render();

  // Update the FPS counter
  void updateFPS();

  // Process the input
  void processInput(float deltaTime);

  // Mouse callback
  static void mouseCallback(GLFWwindow *window, double xpos, double ypos);

private:
  // Window pointer
  GLFWwindow *window_ = nullptr;

  // Shader
  Shader shader_;

  // Meshes
  Mesh cubeMesh_;
  Mesh gridMesh_;

  // Transform
  math::Transform transform_;

  // Camera
  camera::Camera camera_;

  // Sensor system
  sensors::SensorSystem &sensorSystem_;

  // Last time the FPS was updated (persisted across frames)
  double lastTime_ = 0.0;

  // Last frame time
  float lastFrame_ = 0.0f;

  // Frame count
  int frameCount_ = 0;

}; // class Renderer

} // namespace renderer