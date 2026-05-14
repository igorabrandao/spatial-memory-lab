#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "geometry/grid.h"
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

  // Enable depth testing (for 3D rendering)
  glEnable(GL_DEPTH_TEST);

  // -----------------------------
  // Create shader
  // -----------------------------

  // Create the shader from files
  if (!shader.createFromFiles("shaders/basic.vert", "shaders/basic.frag")) {
    cleanup();
    return false;
  }

  // -----------------------------
  // Create meshes
  // -----------------------------

  // Generate the grid mesh
  auto grid = renderer::geometry::generateGrid(20, 1.0f);
  gridMesh.create(grid.data(), grid.size() * sizeof(float));
  gridMesh.setDrawMode(GL_LINES);

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

  // Create the cube mesh
  cubeMesh.create(cubeVertices, sizeof(cubeVertices));

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
    glfwPollEvents(); // Poll events

    update(); // Update the renderer
    render(); // Render the window

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
 * @brief Process the input
 * @param deltaTime The time since the last frame
 */
void Renderer::processInput(float deltaTime) {
  // List of keys to process
  const int keys[] = {GLFW_KEY_W, GLFW_KEY_S,     GLFW_KEY_A,
                      GLFW_KEY_D, GLFW_KEY_SPACE, GLFW_KEY_LEFT_SHIFT};

  // Process the keys
  for (int key : keys) {
    if (glfwGetKey(window, key) == GLFW_PRESS) {
      camera.processKeyboard(key, deltaTime);
    }
  }
}

/**
 * @brief Update the renderer
 * @note Order of operations:
 * 1. Get the current time
 * 2. Calculate delta time
 * 3. Store current frame
 * 4. Process the input (keyboard, mouse, etc.)
 * 5. Update the transform (rotation, position, etc.)
 */
void Renderer::update() {
  // Get the current time
  float currentFrame = (float)glfwGetTime();

  // Calculate delta time
  float deltaTime = currentFrame - lastFrame;

  // Store current frame
  lastFrame = currentFrame;

  // Process the keyboard input
  processInput(deltaTime);

  // Set the rotation of the cube
  // transform.setRotation({currentFrame * 0.5f, currentFrame, 0.0f});

  // Set the position of the cube
  transform.setPosition({0.0f, 0.5f, 0.0f});
}

/**
 * @brief Render the window
 */
void Renderer::render() {
  // Get the framebuffer size
  int width, height;
  glfwGetFramebufferSize(window, &width, &height);

  // Set the height to 1 if it is 0
  height = height == 0 ? 1 : height;

  // Set the viewport to the new size
  glViewport(0, 0, width, height);

  // Clear the color and depth buffers
  glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Use the shader
  shader.use();

  // -----------------------------
  // Create the MVP matrix
  // -----------------------------

  // Create the model matrix
  glm::mat4 model = transform.getModelMatrix();

  // Get the view matrix from the camera
  glm::mat4 view = camera.getViewMatrix();

  // Create the projection matrix
  glm::mat4 projection = glm::perspective(glm::radians(45.0f),
                                          (float)width / height, 0.1f, 100.0f);

  // --- Cube MVP matrix ---
  glm::mat4 cubeMVP = projection * view * model;
  shader.setMat4("MVP", cubeMVP);
  cubeMesh.draw(); // Draw the cube mesh

  // --- Grid MVP matrix ---
  glm::mat4 gridModel = glm::mat4(1.0f);
  glm::mat4 gridMVP = projection * view * gridModel;
  shader.setMat4("MVP", gridMVP);
  gridMesh.draw(); // Draw the grid mesh
}

/**
 * @brief Cleanup the renderer
 */
void Renderer::cleanup() {
  glfwDestroyWindow(window);
  glfwTerminate();

  // Cleanup the mesh and shader
  cubeMesh.cleanup();
  gridMesh.cleanup();
  shader.cleanup();
}

} // namespace renderer