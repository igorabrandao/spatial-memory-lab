#include "grid.h"

namespace renderer {
namespace geometry {

/**
 * @brief Generate a grid on the XZ plane (Y = 0)
 *
 * @param size Number of lines in each direction (grid extends from -size to
 * +size)
 * @param step Distance between lines
 * @return std::vector<float> Vertex data (x, y, z, r, g, b)
 */
std::vector<float> generateGrid(int size, float step) {
  std::vector<float> vertices;

  // Default grid color (gray)
  float r = 0.5f;
  float g = 0.5f;
  float b = 0.5f;

  for (int i = -size; i <= size; i++) {
    float pos = i * step;

    // -----------------------------
    // Lines parallel to the X axis
    // -----------------------------

    // point 1
    vertices.push_back(-size * step); // x
    vertices.push_back(0.0f);         // y
    vertices.push_back(pos);          // z
    vertices.push_back(r);            // r
    vertices.push_back(g);            // g
    vertices.push_back(b);            // b

    // point 2
    vertices.push_back(size * step);
    vertices.push_back(0.0f);
    vertices.push_back(pos);
    vertices.push_back(r);
    vertices.push_back(g);
    vertices.push_back(b);

    // -----------------------------
    // Lines parallel to the Z axis
    // -----------------------------

    // point 1
    vertices.push_back(pos);
    vertices.push_back(0.0f);
    vertices.push_back(-size * step);
    vertices.push_back(r);
    vertices.push_back(g);
    vertices.push_back(b);

    // point 2
    vertices.push_back(pos);
    vertices.push_back(0.0f);
    vertices.push_back(size * step);
    vertices.push_back(r);
    vertices.push_back(g);
    vertices.push_back(b);
  }

  return vertices;
}

} // namespace geometry
} // namespace renderer