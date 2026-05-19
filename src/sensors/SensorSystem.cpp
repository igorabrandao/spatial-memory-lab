#include "SensorSystem.h"
#include "networking/SensorPacket.h"
#include "networking/UdpReceiver.h"

namespace sensors {

/**
 * @brief Constructor
 * @param receiver UdpReceiver reference
 *
 * @note Initializes the orientation to the identity quaternion
 */
SensorSystem::SensorSystem(UdpReceiver &receiver)
    : receiver_(receiver), orientation_(glm::quat(1.0f, 0.0f, 0.0f, 0.0f)) {}

/**
 * @brief Destructor
 */
SensorSystem::~SensorSystem() = default;

/**
 * @brief Get the orientation
 * @return Orientation quaternion
 */
const glm::quat &SensorSystem::getOrientation() const { return orientation_; }

/**
 * @brief Update the sensor system
 */
void SensorSystem::update() {
  // Temporary packet
  SensorPacket packet;

  // Get the latest packet from the receiver
  if (!receiver_.getLatestPacket(packet)) {
    return;
  }

  // Convert the packet to a glm::quat
  // The quaternion is in the order of w, x, y, z
  glm::quat orientation = glm::quat(packet.qw, packet.qx, packet.qy, packet.qz);

  // Normalize and store the orientation
  orientation_ = glm::normalize(orientation);
}

} // namespace sensors