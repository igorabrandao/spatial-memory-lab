#include "file.h"

#include <fstream>
#include <iostream>
#include <sstream>

namespace helpers {

/**
 * @brief Read a file and return the contents as a string
 * @param path const std::string& path to the file
 * @return std::string the contents of the file
 */
std::string File::read(const std::string &path) {
  // Open the file
  std::ifstream file(path);

  // Check if the file was opened successfully
  if (!file.is_open()) {
    std::cerr << "Failed to open file: " << path << "\n";
    return "";
  }

  // Read the file
  std::stringstream buffer;
  buffer << file.rdbuf();

  // Return the contents of the file
  return buffer.str();
}

} // namespace helpers
