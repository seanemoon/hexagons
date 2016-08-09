#include "mgl/call.h"

#include "mgl/includes.h"

#include <string>
#include <iostream>

namespace mgl {

void MaybePrintError(
    const std::string& file, const std::string& fn, int line,
    bool skip_errors) {
  GLenum error_code;
  std::string error_string;
  bool already_printed_header = false;
  while ((error_code = glGetError()) != GL_NO_ERROR) {
    if (skip_errors) continue;
    switch (error_code) {
      case GL_NO_ERROR:
        error_string = "Success.";
        break;
      case GL_INVALID_ENUM:
        error_string = "Invalid enum.";
        break;
      case GL_INVALID_VALUE:
        error_string = "Invalid value.";
        break;
      case GL_INVALID_OPERATION:
        error_string = "Invalid operation.";
        break;
      case GL_INVALID_FRAMEBUFFER_OPERATION:
        error_string = "Invalid framebuffer operation.";
        break;
      case GL_OUT_OF_MEMORY:
        error_string = "Out of memory.";
        break;
      case GL_STACK_UNDERFLOW:
        error_string = "Stack underflow.";
        break;
      case GL_STACK_OVERFLOW:
        error_string = "Stack overflow.";
        break;
    }
    if (!already_printed_header) {
      std::cout << "OpenGL error(s) at "
                << file << ":" << line << " (" << fn << "):"
                << std::endl;
      already_printed_header = true;
    }
    std::cout << "  " <<  error_string << std::endl;
  }
}

}  // namespace mgl
