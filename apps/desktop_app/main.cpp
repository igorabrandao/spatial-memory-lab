#include "renderer/renderer.h"

// -------------------------------------------------------------
// Application entry point
// -------------------------------------------------------------
int main() {
  // Initialize the renderer
  renderer::Renderer renderer;

  // Check if the renderer was initialized successfully
  if (!renderer.init()) {
    // If the renderer was not initialized successfully, return -1
    return -1;
  }

  // Run the renderer
  renderer.run();

  // Cleanup the renderer
  renderer.cleanup();

  // Exit the application
  return 0;
}