#pragma once

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