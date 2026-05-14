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
};

} // namespace camera