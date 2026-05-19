#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>

// Forward declaration (don't include the header file)
class UdpReceiver;

namespace sensors {

/**
 * @brief Sensor system
 * @param receiver UdpReceiver reference
 */
class SensorSystem {
public:
  // Constructor
  SensorSystem(UdpReceiver &receiver);

  // Destructor
  ~SensorSystem();

  // Get the orientation
  const glm::quat& getOrientation() const;

  // Update the sensor system
  void update();

private:
  // UdpReceiver reference
  UdpReceiver &receiver_;

  // Orientation (in quaternion)
  glm::quat orientation_;
};

} // namespace sensors