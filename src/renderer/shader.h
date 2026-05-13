#pragma once

#include <glm/glm.hpp>
#include <string>

namespace renderer {

class Shader {
public:
  // Create the shader
  bool create(const char *vertexSrc, const char *fragmentSrc);

  // Create the shader from files
  bool createFromFiles(const std::string &vertexPath,
                       const std::string &fragmentPath);

  // Use the shader
  void use() const;

  // Set the matrix uniform
  void setMat4(const std::string &name, const glm::mat4 &mat) const;

  // Cleanup the shader
  void cleanup();

private:
  // Shader program
  unsigned int program = 0;
};

} // namespace renderer