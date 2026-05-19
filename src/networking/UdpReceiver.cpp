#include "UdpReceiver.h"

#include <arpa/inet.h>
#include <cerrno>
#include <chrono>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>
#include <thread>
#include <unistd.h>

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

  // Create a UDP socket
  socket_fd_ = socket(AF_INET, SOCK_DGRAM, 0);

  // Check if the UDP socket was created successfully
  if (socket_fd_ < 0) {
    std::cerr << "Failed to create UDP socket\n";
    return false;
  }

  // Get the socket flags
  int flags = fcntl(socket_fd_, F_GETFL, 0);

  // Check if the socket flags were retrieved successfully
  if (flags < 0) {
    std::cerr << "Failed to get socket flags\n";
    close(socket_fd_);
    socket_fd_ = -1;
    return false;
  }

  // Set the socket to non-blocking
  flags |= O_NONBLOCK;

  // Check if the socket flags were set successfully
  if (fcntl(socket_fd_, F_SETFL, flags) < 0) {
    std::cerr << "Failed to set socket to non-blocking\n";
    close(socket_fd_);
    socket_fd_ = -1;
    return false;
  }

  // Configure socket address
  sockaddr_in address{};

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(port);

  // Bind the UDP socket to the address
  if (bind(socket_fd_, reinterpret_cast<sockaddr *>(&address),
           sizeof(address)) < 0) {
    std::cerr << "Failed to bind UDP socket\n";
    close(socket_fd_);
    socket_fd_ = -1;
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
    return;
  }

  // Set the running flag to false
  running_ = false;

  // Join the receive thread
  if (receive_thread_.joinable()) {
    receive_thread_.join();
  }

  // Close the socket
  if (socket_fd_ >= 0) {
    close(socket_fd_);
    socket_fd_ = -1;
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
    // Create a packet
    SensorPacket packet{};

    // Create a sender address
    sockaddr_in sender_address{};
    socklen_t sender_length = sizeof(sender_address);

    // Receive the packet from the UDP socket
    ssize_t received_bytes =
        recvfrom(socket_fd_, &packet, sizeof(SensorPacket), 0,
                 reinterpret_cast<sockaddr *>(&sender_address), &sender_length);

    // Check if the packet was received successfully
    if (received_bytes < 0) {
      const bool would_block = errno == EWOULDBLOCK || errno == EAGAIN;

      if (would_block) {
        // Non-blocking operation, sleep for a short time and continue
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        continue;
      }

      // Real error
      std::cerr << "Error receiving packet: " << strerror(errno) << "\n";
      running_ = false;
      break;
    }

    // Check if the packet size is valid
    if (received_bytes != sizeof(SensorPacket)) {
      std::cerr << "Invalid packet size: " << received_bytes << "\n";
      continue;
    }

    {
      // Lock the packet mutex
      std::lock_guard<std::mutex> lock(packet_mutex_);

      // Copy the packet to the latest packet
      latest_packet_ = packet;

      // Set the has packet flag to true
      has_packet_ = true;
    }

    // Increment the packet counter
    packet_counter_++;

    // Log the received packet every 100 packets
    if (packet_counter_ % 100 == 0) {
      // Log the received packet
      std::cout << "Received packet: "
                << "qx=" << packet.qx << " "
                << "qy=" << packet.qy << " "
                << "qz=" << packet.qz << " "
                << "qw=" << packet.qw << "\n";
    }
  }
}