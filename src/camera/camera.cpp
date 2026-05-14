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
 * @brief Get the right vector
 * @return The right vector
 */
glm::vec3 Camera::getRight() const {
  return glm::normalize(glm::cross(getFront(), glm::vec3(0, 1, 0)));
}

/**
 * @brief Get the up vector
 * @return The up vector
 */
glm::vec3 Camera::getUp() const { return glm::vec3(0, 1, 0); }

/**
 * @brief Get the down vector
 * @return The down vector
 */
glm::vec3 Camera::getDown() const { return glm::vec3(0, -1, 0); }

/**
 * @brief Get the view matrix
 * @return The view matrix
 */
glm::mat4 Camera::getViewMatrix() const {
  return glm::lookAt(position, position + getFront(),
                     glm::vec3(0.0f, 1.0f, 0.0f));
}

/**
 * @brief Move the camera forward
 * @param deltaTime The time since the last frame
 */
void Camera::moveForward(float deltaTime) {
  position += getFront() * speed * deltaTime;
}

/**
 * @brief Move the camera backward
 * @param deltaTime The time since the last frame
 */
void Camera::moveBackward(float deltaTime) {
  position -= getFront() * speed * deltaTime;
}

/**
 * @brief Move the camera left
 * @param deltaTime The time since the last frame
 */
void Camera::moveLeft(float deltaTime) {
  position -= getRight() * speed * deltaTime;
}

/**
 * @brief Move the camera right
 * @param deltaTime The time since the last frame
 */
void Camera::moveRight(float deltaTime) {
  position += getRight() * speed * deltaTime;
}

/**
 * @brief Move the camera up
 * @param deltaTime The time since the last frame
 */
void Camera::moveUp(float deltaTime) {
  position += getUp() * speed * deltaTime;
}

/**
 * @brief Move the camera down
 * @param deltaTime The time since the last frame
 */
void Camera::moveDown(float deltaTime) {
  position -= getUp() * speed * deltaTime;
}

/**
 * @brief Process keyboard input
 * @param key The key pressed
 * @param deltaTime The time since the last frame
 */
void Camera::processKeyboard(int key, float deltaTime) {
  if (key == GLFW_KEY_W)
    moveForward(deltaTime);
  if (key == GLFW_KEY_S)
    moveBackward(deltaTime);
  if (key == GLFW_KEY_A)
    moveLeft(deltaTime);
  if (key == GLFW_KEY_D)
    moveRight(deltaTime);
  if (key == GLFW_KEY_SPACE)
    moveUp(deltaTime);
  if (key == GLFW_KEY_LEFT_SHIFT)
    moveDown(deltaTime);
}

/**
 * @brief Process mouse input
 * @param xoffset The x offset
 * @param yoffset The y offset
 */
void Camera::processMouse(float xoffset, float yoffset) {
  // Multiply the offset by the sensitivity
  xoffset *= sensitivity;
  yoffset *= sensitivity;

  // Update the yaw and pitch
  yaw += xoffset;
  pitch += yoffset;

  // Clamp the pitch
  if (pitch > 89.0f)
    pitch = 89.0f; // Limit the pitch to 89 degrees
  if (pitch < -89.0f)
    pitch = -89.0f; // Limit the pitch to -89 degrees
}

} // namespace camera