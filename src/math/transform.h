#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

namespace math {

class Transform {
public:
  Transform();

  // Set the position
  void setPosition(const glm::vec3 &pos);

  // Set the rotation
  void setRotation(const glm::quat &rot);

  // Set the scale
  void setScale(const glm::vec3 &scl);

  // Get the model matrix
  glm::mat4 getModelMatrix() const;

private:
  // Position (vector)
  glm::vec3 position_;

  // Rotation (quaternion)
  glm::quat rotation_;

  // Scale (multiplicative vector)
  glm::vec3 scale_;
};

} // namespace math