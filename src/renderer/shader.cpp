#define GLFW_INCLUDE_NONE

#include <GLFW/glfw3.h>
#include <OpenGL/gl3.h>

#include "helpers/file.h"
#include "shader.h"

#include <iostream>

namespace renderer {

/**
 * @brief Create the shader
 * @param vertexSrc const char* vertex shader source
 * @param fragmentSrc const char* fragment shader source
 * @return bool true if the shader was created successfully, false otherwise
 */
bool Shader::create(const char *vertexSrc, const char *fragmentSrc) {
  // Success flag
  int success = 0;

  // Info log buffer
  char infoLog[1024] = {0};

  // Delete the program if it exists (leaking memory)
  if (program) {
    glDeleteProgram(program);
    program = 0;
  }

  // -----------------------------
  // Create the vertex shader
  // -----------------------------
  unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertexShader, 1, &vertexSrc, nullptr);
  glCompileShader(vertexShader);

  // Get the compilation status
  glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(vertexShader, 1024, nullptr, infoLog);
    std::cerr << "Vertex shader compilation failed: " << infoLog << "\n";
    glDeleteShader(vertexShader); // Delete the shader
    return false;
  }

  // -----------------------------
  // Create the fragment shader
  // -----------------------------
  unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragmentShader, 1, &fragmentSrc, nullptr);
  glCompileShader(fragmentShader);

  glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(fragmentShader, 1024, nullptr, infoLog);
    std::cerr << "Fragment shader compilation failed: " << infoLog << "\n";
    glDeleteShader(vertexShader);   // Delete the vertex shader
    glDeleteShader(fragmentShader); // Delete the fragment shader
    return false;
  }

  // -----------------------------
  // Create the shader program
  // -----------------------------
  program = glCreateProgram();

  // -----------------------------
  // Attach the shaders to the program
  // -----------------------------
  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);

  // Link the program
  glLinkProgram(program);

  // Get the link status
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(program, 1024, nullptr, infoLog);
    std::cerr << "Shader program linking failed: " << infoLog << "\n";

    // Delete the program
    if (program) {
      glDeleteProgram(program);
    }

    glDeleteShader(vertexShader);   // Delete the vertex shader
    glDeleteShader(fragmentShader); // Delete the fragment shader
    return false;
  }

  // Detach the shaders from the program
  glDetachShader(program, vertexShader);
  glDetachShader(program, fragmentShader);

  // Delete the shaders
  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);

  return true;
}

/**
 * @brief Create the shader from files
 * @param vertexPath const std::string& path to the vertex shader file
 * @param fragmentPath const std::string& path to the fragment shader file
 * @return bool true if the shader was created successfully, false otherwise
 */
bool Shader::createFromFiles(const std::string &vertexPath,
                          const std::string &fragmentPath) {

  // Read the files
  std::string vertexCode = helpers::File::read(vertexPath);
  std::string fragmentCode = helpers::File::read(fragmentPath);

  // Check if the files were read successfully
  if (vertexCode.empty() || fragmentCode.empty()) {
    std::cerr << "Failed to load shader files: " << vertexPath << " or "
              << fragmentPath << "\n";
    return false;
  }

  // Convert the code to const char*
  const char *vSrc = vertexCode.c_str();
  const char *fSrc = fragmentCode.c_str();

  // Create the shader
  return create(vSrc, fSrc);
}

/**
 * @brief Use the shader
 */
void Shader::use() const {
  if (program) {
    glUseProgram(program);
  }
}

/**
 * @brief Cleanup the shader and delete the program
 */
void Shader::cleanup() {
  if (program) {
    glDeleteProgram(program);
    program = 0;
  }
}

} // namespace renderer