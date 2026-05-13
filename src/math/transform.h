#pragma once

#include <glm/glm.hpp>

namespace math {

class Transform {
public:
  Transform();

  // Set the position
  void setPosition(const glm::vec3 &pos);

  // Set the rotation
  void setRotation(const glm::vec3 &rot);

  // Set the scale
  void setScale(const glm::vec3 &scl);

  // Get the model matrix
  glm::mat4 getModelMatrix() const;

private:
  // Position
  glm::vec3 position;

  // Rotation
  glm::vec3 rotation;

  // Scale
  glm::vec3 scale;
};

} // namespace math