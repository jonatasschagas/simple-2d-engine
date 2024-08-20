#include "OpenGLHeaders.h"
#include <cassert>
#include <iostream>
#include <string>

/**
 * @brief Check for OpenGL errors and print an error message if there is one.
 *
 * @param errorMsg The error message to print.
 */
inline void checkOpenGLError(std::string const& errorMsg) {
  GLenum err;
  while ((err = glGetError()) != GL_NO_ERROR) {
    std::string error;

    switch (err) {
      case GL_INVALID_ENUM:
        error = "GL_INVALID_ENUM";
        break;
      case GL_INVALID_VALUE:
        error = "GL_INVALID_VALUE";
        break;
      case GL_INVALID_OPERATION:
        error = "GL_INVALID_OPERATION";
        break;
      case GL_STACK_OVERFLOW:
        error = "GL_STACK_OVERFLOW";
        break;
      case GL_STACK_UNDERFLOW:
        error = "GL_STACK_UNDERFLOW";
        break;
      case GL_OUT_OF_MEMORY:
        error = "GL_OUT_OF_MEMORY";
        break;
      case GL_INVALID_FRAMEBUFFER_OPERATION:
        error = "GL_INVALID_FRAMEBUFFER_OPERATION";
        break;
      default:
        error = "UNKNOWN_ERROR";
        break;
    }

    std::cerr << "OpenGL Error: " << error << " - " << errorMsg << std::endl;
    assert(false);  // This will stop the program and print the error message.
  }
}