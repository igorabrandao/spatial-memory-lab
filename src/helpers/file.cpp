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
  std::ifstream file(path);

  if (!file.is_open()) {
    std::cerr << "Failed to open file: " << path << "\n";
    return "";
  }

  std::stringstream buffer;
  buffer << file.rdbuf();

  return buffer.str();
}

} // namespace helpers
