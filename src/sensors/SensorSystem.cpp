#include "SensorSystem.h"

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
  // TODO
}

} // namespace sensors