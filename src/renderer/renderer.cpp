#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>

#include "mesh.h"
#include "renderer.h"
#include "shader.h"

#include <iostream>
#include <string>

namespace renderer {

/**
 * @brief Callback function for when the framebuffer size changes
 * @param window GLFWwindow* pointer to the window
 * @param width int new width
 * @param height int new height
 */
static void framebuffer_size_callback(GLFWwindow *, int w, int h) {
  // Set the viewport to the new size
  glViewport(0, 0, w, h);
}

/**
 * @brief Initialize the renderer
 * @return bool true if the renderer was initialized successfully, false
 * otherwise
 */
bool Renderer::init() {
  // Initialize GLFW
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW\n";
    return false;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  // Create the window
  window = glfwCreateWindow(800, 600, "Spatial Memory Lab", nullptr, nullptr);

  if (!window) {
    std::cerr << "Failed to create window\n";
    glfwTerminate();
    return false;
  }

  // Make the context current
  glfwMakeContextCurrent(window);
  glfwSwapInterval(1);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  // -----------------------------
  // Create shader
  // -----------------------------

  // Create the shader from files
  if (!shader.createFromFiles("shaders/basic.vert", "shaders/basic.frag")) {
    cleanup();
    return false;
  }

  // -----------------------------
  // Create mesh
  // -----------------------------

  // Define the vertices
  float cubeVertices[] = {
      // positions        // colors

      // front
      -0.5f,
      -0.5f,
      0.5f,
      1,
      0,
      0,
      0.5f,
      -0.5f,
      0.5f,
      0,
      1,
      0,
      0.5f,
      0.5f,
      0.5f,
      0,
      0,
      1,

      0.5f,
      0.5f,
      0.5f,
      0,
      0,
      1,
      -0.5f,
      0.5f,
      0.5f,
      1,
      1,
      0,
      -0.5f,
      -0.5f,
      0.5f,
      1,
      0,
      0,

      // back
      -0.5f,
      -0.5f,
      -0.5f,
      1,
      0,
      1,
      0.5f,
      -0.5f,
      -0.5f,
      0,
      1,
      1,
      0.5f,
      0.5f,
      -0.5f,
      1,
      1,
      1,

      0.5f,
      0.5f,
      -0.5f,
      1,
      1,
      1,
      -0.5f,
      0.5f,
      -0.5f,
      0.5,
      0.5,
      0.5,
      -0.5f,
      -0.5f,
      -0.5f,
      1,
      0,
      1,

      // left
      -0.5f,
      0.5f,
      0.5f,
      1,
      0,
      0,
      -0.5f,
      0.5f,
      -0.5f,
      0,
      1,
      0,
      -0.5f,
      -0.5f,
      -0.5f,
      0,
      0,
      1,

      -0.5f,
      -0.5f,
      -0.5f,
      0,
      0,
      1,
      -0.5f,
      -0.5f,
      0.5f,
      1,
      1,
      0,
      -0.5f,
      0.5f,
      0.5f,
      1,
      0,
      0,

      // right
      0.5f,
      0.5f,
      0.5f,
      1,
      0,
      1,
      0.5f,
      0.5f,
      -0.5f,
      0,
      1,
      1,
      0.5f,
      -0.5f,
      -0.5f,
      1,
      1,
      1,

      0.5f,
      -0.5f,
      -0.5f,
      1,
      1,
      1,
      0.5f,
      -0.5f,
      0.5f,
      0.5,
      0.5,
      0.5,
      0.5f,
      0.5f,
      0.5f,
      1,
      0,
      1,

      // top
      -0.5f,
      0.5f,
      -0.5f,
      1,
      0,
      0,
      0.5f,
      0.5f,
      -0.5f,
      0,
      1,
      0,
      0.5f,
      0.5f,
      0.5f,
      0,
      0,
      1,

      0.5f,
      0.5f,
      0.5f,
      0,
      0,
      1,
      -0.5f,
      0.5f,
      0.5f,
      1,
      1,
      0,
      -0.5f,
      0.5f,
      -0.5f,
      1,
      0,
      0,

      // bottom
      -0.5f,
      -0.5f,
      -0.5f,
      1,
      0,
      1,
      0.5f,
      -0.5f,
      -0.5f,
      0,
      1,
      1,
      0.5f,
      -0.5f,
      0.5f,
      1,
      1,
      1,

      0.5f,
      -0.5f,
      0.5f,
      1,
      1,
      1,
      -0.5f,
      -0.5f,
      0.5f,
      0.5,
      0.5,
      0.5,
      -0.5f,
      -0.5f,
      -0.5f,
      1,
      0,
      1,
  };

  // Create the mesh
  mesh.create(cubeVertices, sizeof(cubeVertices));

  // -----------------------------
  // Viewport
  // -----------------------------
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);
  glViewport(0, 0, width, height);

  lastTime = glfwGetTime();
  frameCount = 0;

  return true;
}

/**
 * @brief Run the renderer
 */
void Renderer::run() {
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();        // Poll events
    render();                // Render the window
    glfwSwapBuffers(window); // Swap buffers
    updateFPS();             // Update the FPS counter
  }
}

/**
 * @brief Update the FPS counter
 */
void Renderer::updateFPS() {
  double currentTime = glfwGetTime();
  frameCount++;

  // Update the FPS counter if 1 second has passed
  if (currentTime - lastTime >= 1.0) {
    // Set the window title to the FPS
    std::string title =
        "Spatial Memory Lab - FPS: " + std::to_string(frameCount);
    glfwSetWindowTitle(window, title.c_str());

    // Reset the frame count and last time
    frameCount = 0;
    lastTime = currentTime;
  }
}

/**
 * @brief Render the window
 */
void Renderer::render() {
  // Clear the color buffer
  glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  // Use the shader
  shader.use();

  // Draw the mesh
  mesh.draw();
}

/**
 * @brief Cleanup the renderer
 */
void Renderer::cleanup() {
  glfwDestroyWindow(window);
  glfwTerminate();

  // Cleanup the mesh and shader
  mesh.cleanup();
  shader.cleanup();
}

} // namespace renderer