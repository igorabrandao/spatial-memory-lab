#pragma once

#include <string>

namespace helpers {

/**
 * @brief File-system helpers grouped as a static utility class.
 *
 * The class is intentionally non-instantiable: it only exposes static
 * methods. Group future file helpers (write, exists, …) here as static
 * members so all file I/O lives in a single translation unit.
 */
class File {
public:
  File() = delete;

  /**
   * @brief Read a text file entirely into a string.
   *
   * Logs the error to stderr and returns an empty string when the file
   * cannot be opened. Callers that need to distinguish "empty file" from
   * "open failed" should check existence beforehand.
   *
   * @param path Filesystem path to the file.
   * @return File contents as a string, or "" on failure.
   */
  static std::string read(const std::string &path);
};

} // namespace helpers
