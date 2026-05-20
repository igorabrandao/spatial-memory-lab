#include "transform.h"
#include <glm/gtc/matrix_transform.hpp>

namespace math {

/**
 * @brief Constructor
 * @return Transform
 *
 * @note The rotation is initialized to an identity quaternion
 */
Transform::Transform()
    : position_(0.0f), rotation_(1.0f, 0.0f, 0.0f, 0.0f), scale_(1.0f) {}

/**
 * @brief Set the position
 * @param pos const glm::vec3& position
 */
void Transform::setPosition(const glm::vec3 &pos) { position_ = pos; }

/**
 * @brief Set the rotation
 * @param rot const glm::quat& rotation
 */
void Transform::setRotation(const glm::quat &rot) { rotation_ = rot; }

/**
 * @brief Set the scale
 * @param scl const glm::vec3& scale
 */
void Transform::setScale(const glm::vec3 &scl) { scale_ = scl; }

/**
 * @brief Get the model matrix
 * @return glm::mat4 model matrix
 */
glm::mat4 Transform::getModelMatrix() const {
  // Create the model matrix
  glm::mat4 model = glm::mat4(1.0f);

  // Translate the model matrix
  model = glm::translate(model, position_);

  // Rotate the model matrix
  glm::mat4 rotationMatrix = glm::mat4_cast(rotation_);

  // Multiply the model matrix by the rotation matrix
  model = model * rotationMatrix;

  // Scale the model matrix
  model = glm::scale(model, scale_);

  // Return the model matrix
  return model;
}

} // namespace math