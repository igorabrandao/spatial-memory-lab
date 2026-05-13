#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>

#include "mesh.h"

namespace renderer {

/**
 * @brief Create mesh from raw vertex data
 * @param vertices const float* vertices
 * @param size unsigned int size
 * @return bool true if the mesh was created successfully, false otherwise
 */
bool Mesh::create(const float *vertices, unsigned int size) {
  // Calculate the number of vertices (3 vertices per triangle x, y, z, r, g, b)
  vertexCount = size / (6 * sizeof(float));

  // Create the vertex array object
  glGenVertexArrays(1, &VAO);
  glBindVertexArray(VAO);

  // Create the vertex buffer object
  glGenBuffers(1, &VBO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

  // Configure the vertex attributes
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);

  // Configure the color attribute
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  // Unbind the vertex array object
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  // Return success flag
  return true;
}

/**
 * @brief Draw the mesh
 */
void Mesh::draw() const {
  // Bind the vertex array object
  glBindVertexArray(VAO);

  // Draw the mesh
  glDrawArrays(GL_TRIANGLES, 0, vertexCount);

  // Unbind the vertex array object
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

/**
 * @brief Cleanup GPU resources
 */
void Mesh::cleanup() {
  if (VBO) {
    glDeleteBuffers(1, &VBO);
    VBO = 0;
  }
  if (VAO) {
    glDeleteVertexArrays(1, &VAO);
    VAO = 0;
  }
  if (EBO) {
    glDeleteBuffers(1, &EBO);
    EBO = 0;
  }
}

} // namespace renderer