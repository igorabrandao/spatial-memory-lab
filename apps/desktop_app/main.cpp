#include "networking/UdpReceiver.h"
#include "renderer/renderer.h"
#include "sensors/SensorSystem.h"

// -------------------------------------------------------------
// Application entry point
// -------------------------------------------------------------
int main() {
  // Initialize the UDP receiver
  UdpReceiver receiver;

  // Start the UDP receiver
  receiver.start(5005);

  // Initialize the sensor system
  sensors::SensorSystem sensorSystem(receiver);

  // Initialize the renderer
  renderer::Renderer renderer(sensorSystem);

  // Check if the renderer was initialized successfully
  if (!renderer.init()) {
    // If the renderer was not initialized successfully, return -1
    return -1;
  }

  // Run the renderer
  renderer.run();

  // Cleanup the renderer
  renderer.cleanup();

  // Stop the UDP receiver
  receiver.stop();

  // Exit the application
  return 0;
}