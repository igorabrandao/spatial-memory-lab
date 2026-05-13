#include "transform.h"
#include <glm/gtc/matrix_transform.hpp>

namespace math {

/**
 * @brief Constructor
 * @return Transform
 */
Transform::Transform() : position(0.0f), rotation(0.0f), scale(1.0f) {}

/**
 * @brief Set the position
 * @param pos const glm::vec3& position
 */
void Transform::setPosition(const glm::vec3 &pos) { position = pos; }

/**
 * @brief Set the rotation
 * @param rot const glm::vec3& rotation
 */
void Transform::setRotation(const glm::vec3 &rot) { rotation = rot; }

/**
 * @brief Set the scale
 * @param scl const glm::vec3& scale
 */
void Transform::setScale(const glm::vec3 &scl) { scale = scl; }

/**
 * @brief Get the model matrix
 * @return glm::mat4 model matrix
 */
glm::mat4 Transform::getModelMatrix() const {
  // Create the model matrix
  glm::mat4 model = glm::mat4(1.0f);

  // Translate the model matrix
  model = glm::translate(model, position);

  // Rotate the model matrix
  model = glm::rotate(model, rotation.x, glm::vec3(1, 0, 0));
  model = glm::rotate(model, rotation.y, glm::vec3(0, 1, 0));
  model = glm::rotate(model, rotation.z, glm::vec3(0, 0, 1));

  // Scale the model matrix
  model = glm::scale(model, scale);

  // Return the model matrix
  return model;
}

} // namespace math