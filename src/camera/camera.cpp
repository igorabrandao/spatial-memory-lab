#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

#include "camera.h"

#include <cmath>

namespace camera {

/**
 * @brief Constructor
 * @param position The position of the camera
 * @param yaw The yaw of the camera
 * @param pitch The pitch of the camera
 * @param speed The speed of the camera
 * @param sensitivity The sensitivity of the camera
 */
Camera::Camera()
    : position(0.0f, 1.0f, 3.0f), yaw(-90.0f), pitch(0.0f), speed(3.0f),
      sensitivity(0.1f) {}

/**
 * @brief Get the front vector
 * @return The front vector
 *
 * @note I have 2 angles and need to know where the camera is looking at in the
 * 3D space.
 */
glm::vec3 Camera::getFront() const {
  // Create the front vector (x, y, z)
  glm::vec3 front;

  // Calculate the front vector (using trigonometric functions)
  front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
  front.y = sin(glm::radians(pitch));
  front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

  // Normalize the front vector to ensure it has a length of 1
  return glm::normalize(front);
}

/**
 * @brief Get the view matrix
 * @return The view matrix
 */
glm::mat4 Camera::getViewMatrix() const {
  return glm::lookAt(position, position + getFront(),
                     glm::vec3(0.0f, 1.0f, 0.0f));
}

/**
 * @brief Process keyboard input
 * @param key The key pressed
 * @param deltaTime The time since the last frame
 */
void Camera::processKeyboard(int key, float deltaTime) {
  float velocity = speed * deltaTime;
  glm::vec3 front = getFront();
  glm::vec3 right = glm::normalize(glm::cross(front, glm::vec3(0, 1, 0)));

  if (key == GLFW_KEY_W)
    position += front * velocity;
  if (key == GLFW_KEY_S)
    position -= front * velocity;
  if (key == GLFW_KEY_A)
    position -= right * velocity;
  if (key == GLFW_KEY_D)
    position += right * velocity;
}

/**
 * @brief Process mouse input
 * @param xoffset The x offset
 * @param yoffset The y offset
 */
void Camera::processMouse(float xoffset, float yoffset) {
  xoffset *= sensitivity;
  yoffset *= sensitivity;

  yaw += xoffset;
  pitch += yoffset;

  if (pitch > 89.0f)
    pitch = 89.0f;
  if (pitch < -89.0f)
    pitch = -89.0f;
}

} // namespace camera