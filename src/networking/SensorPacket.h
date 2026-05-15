#pragma once

#include <cstdint>

// Pack the struct to 1 byte alignment
#pragma pack(push, 1)

struct SensorPacket {
  // Version of the packet format
  uint8_t version;

  // Timestamp of the packet in nanoseconds
  uint64_t timestamp_ns;

  // Quaternion of the sensor
  float qx;
  float qy;
  float qz;
  float qw;
};

#pragma pack(pop)

/**
 * @brief Assert the size of the SensorPacket struct is 25 bytes
 *
 * @note This is a static assertion to ensure the size of the SensorPacket
 * struct is 25 bytes.
 *
 * @note The size of the SensorPacket struct is calculated as follows:
 * uint8_t   = 1
 * uint64_t  = 8
 * 4 floats  = 16
 * ----------------
 * total     = 25 bytes
 */
static_assert(sizeof(SensorPacket) == 25, "SensorPacket size is not 25 bytes");