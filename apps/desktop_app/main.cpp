#define GL_SILENCE_DEPRECATION

#include <OpenGL/gl3.h>
#include <GLFW/glfw3.h>
#include <iostream>

int main() {
  // Initialize GLFW
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW\n";
    return -1;
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
    return -1;
  }

  // Make context current
  glfwMakeContextCurrent(window);

  // Set viewport
  glViewport(0, 0, 800, 600);

  // Main loop
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();

    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(window);
  }

  // Cleanup
  glfwDestroyWindow(window);
  glfwTerminate();

  return 0;
}