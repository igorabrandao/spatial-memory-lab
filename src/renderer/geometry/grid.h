#pragma once

#include <vector>

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
std::vector<float> generateGrid(int size, float step);

} // namespace geometry
} // namespace renderer