#define GL_SILENCE_DEPRECATION

#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>
#include <iostream>
#include <string>

/**
 * @brief Callback function for when the framebuffer size changes
 * @param window GLFWwindow* pointer to the window
 * @param width int new width
 * @param height int new height
 */
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  // Set the viewport to the new size
  glViewport(0, 0, width, height);
}

/**
 * @brief Initialize the window
 * @return GLFWwindow* pointer to the window
 */
GLFWwindow *initWindow() {
  // Initialize GLFW
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW\n";
    return nullptr;
  }

  // Configure OpenGL context (important for macOS)
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  // Create window
  GLFWwindow *window =
      glfwCreateWindow(800, 600, "Spatial Memory Lab", nullptr, nullptr);

  if (!window) {
    std::cerr << "Failed to create window\n";
    glfwTerminate();
    return nullptr;
  }

  // Make context current
  glfwMakeContextCurrent(window);

  // Enable vsync
  glfwSwapInterval(1);

  // Set the framebuffer size callback
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // Set viewport
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);

  return window;
}

/**
 * @brief Render the window
 */
void render() {
  // Clear the color buffer
  glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

/**
 * @brief Update the FPS counter
 * @param window GLFWwindow* pointer to the window
 * @param lastTime double reference to the last time
 * @param frameCount int reference to the frame count
 */
void updateFPS(GLFWwindow *window, double &lastTime, int &frameCount) {
  // FPS calculation
  double currentTime = glfwGetTime();
  frameCount++;

  if (currentTime - lastTime >= 1.0) {
    std::string title = "Spatial Memory Lab - FPS: " + std::to_string(frameCount);
    glfwSetWindowTitle(window, title.c_str());

    frameCount = 0;
    lastTime = currentTime; // Reset the last time
  }
}

/**
 * @brief Run the application
 * @param window GLFWwindow* pointer to the window
 */
void run(GLFWwindow *window) {
  // Initialize the FPS counter
  double lastTime = glfwGetTime();
  int frameCount = 0;

  // Run the application
  while (!glfwWindowShouldClose(window)) {
    // Poll events
    glfwPollEvents();

    // Render the window
    render();

    // Swap buffers
    glfwSwapBuffers(window);

    // Update the FPS counter
    updateFPS(window, lastTime, frameCount);
  }
}

/**
 * @brief Cleanup the window
 * @param window GLFWwindow* pointer to the window
 */
void cleanup(GLFWwindow *window) {
  // Destroy the window
  glfwDestroyWindow(window);
  // Terminate GLFW
  glfwTerminate();
}

// -------------------------------------------------------------
// Application entry point
// -------------------------------------------------------------
int main() {
  // Initialize window
  GLFWwindow *window = initWindow();

  // Check if window was created successfully
  if (!window) {
    return -1;
  }

  // Run the application
  run(window);

  // Cleanup
  cleanup(window);

  return 0;
}