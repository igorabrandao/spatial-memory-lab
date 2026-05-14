#pragma once

#include <glm/glm.hpp>

namespace camera {

class Camera {
public:
  // Constructor
  Camera();

  // Get the view matrix
  glm::mat4 getViewMatrix() const;

  // Process keyboard input
  void processKeyboard(int key, float deltaTime);
  void processMouse(float xoffset, float yoffset);

  // Camera movement
  void moveForward(float deltaTime);
  void moveBackward(float deltaTime);
  void moveLeft(float deltaTime);
  void moveRight(float deltaTime);
  void moveUp(float deltaTime);
  void moveDown(float deltaTime);

private:
  // Position
  glm::vec3 position;

  // Yaw (horizontal rotation - left/right)
  float yaw;

  // Pitch (vertical inclination - up/down)
  float pitch;

  // Speed
  float speed;
  float sensitivity;

  // Get the front vector
  glm::vec3 getFront() const;
  glm::vec3 getRight() const;
  glm::vec3 getUp() const;
  glm::vec3 getDown() const;
};

} // namespace camera