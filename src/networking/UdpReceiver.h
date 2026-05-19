#pragma once

#include <atomic>
#include <mutex>
#include <thread>

#include "SensorPacket.h"

class UdpReceiver {
public:
  // Constructor
  UdpReceiver();

  // Destructor
  ~UdpReceiver();

  // Start the UDP receiver
  bool start(unsigned short port);

  // Stop the UDP receiver
  void stop();

  // Get the latest packet
  bool getLatestPacket(SensorPacket &outPacket);

private:
  // Receive loop
  void receiveLoop();

private:
  // Socket file descriptor
  int socket_fd_;

  // Receive thread
  std::thread receive_thread_;

  // Running flag
  std::atomic<bool> running_;

  // Packet mutex
  std::mutex packet_mutex_;

  // Latest packet
  SensorPacket latest_packet_;

  // Has packet flag
  bool has_packet_;

  // Packet count
  unsigned int packet_counter_;
};