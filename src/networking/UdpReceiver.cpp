#include "UdpReceiver.h"

#include <chrono>
#include <iostream>

/**
 * @brief Constructor
 *
 * @note Initializes the UDP receiver
 */
UdpReceiver::UdpReceiver()
    : socket_fd_(-1), running_(false), has_packet_(false) {}

/**
 * @brief Destructor
 *
 * @note Stops the UDP receiver
 */
UdpReceiver::~UdpReceiver() { stop(); }

/**
 * @brief Start the UDP receiver
 *
 * @param port The port to receive on
 *
 * @return True if the UDP receiver was started successfully, false otherwise
 */
bool UdpReceiver::start(unsigned short port) {
  // Check if the UDP receiver is already running
  if (running_) {
    std::cerr << "UDP receiver already running\n";
    return false;
  }

  // Set the running flag to true
  running_ = true;

  // Start the receive thread
  receive_thread_ = std::thread(&UdpReceiver::receiveLoop, this);

  // Log the start of the UDP receiver
  std::cout << "UDP receiver thread started on port " << port << "\n";
  return true;
}

/**
 * @brief Stop the UDP receiver
 */
void UdpReceiver::stop() {
  // Check if the UDP receiver is not running
  if (!running_) {
    std::cerr << "UDP receiver not running\n";
    return;
  }

  // Set the running flag to false
  running_ = false;

  // Join the receive thread
  if (receive_thread_.joinable()) {
    receive_thread_.join();
  }

  // Log the stop of the UDP receiver
  std::cout << "UDP receiver thread stopped\n";
}

/**
 * @brief Get the latest packet
 *
 * @param outPacket The output packet
 *
 * @return True if a packet was received, false otherwise
 */
bool UdpReceiver::getLatestPacket(SensorPacket &outPacket) {
  // Check if there is a packet available
  std::lock_guard<std::mutex> lock(packet_mutex_);

  // Check if there is no packet available
  if (!has_packet_) {
    std::cerr << "No packet available\n";
    return false;
  }

  // Copy the latest packet to the output packet
  outPacket = latest_packet_;

  // Set the has packet flag to false
  has_packet_ = false;

  // Return true
  return true;
}

/**
 * @brief Receive loop
 *
 * @note Receives packets from the UDP socket
 */
void UdpReceiver::receiveLoop() {
  // While the UDP receiver is running
  while (running_) {
    // Sleep for 100 milliseconds
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}