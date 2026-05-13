#pragma once

namespace renderer {

class Mesh {
public:
  // Create mesh from raw vertex data
  bool create(const float *vertices, unsigned int size);

  // Draw the mesh
  void draw() const;

  // Cleanup GPU resources
  void cleanup();

private:
  // Vertex Buffer Object
  unsigned int VBO = 0;

  // Vertex Array Object
  unsigned int VAO = 0;

  // Element Buffer Object
  unsigned int EBO = 0;

  // Number of vertices
  unsigned int vertexCount = 0;
};

} // namespace renderer