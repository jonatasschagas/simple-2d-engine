#pragma once
#ifndef OPENGLHEADERS_H
#define OPENGLHEADERS_H

#ifdef APPLE
#include <glad/glad.h>
#endif

#ifdef __ANDROID__
#include <GLES3/gl3.h>
#endif

#endif

#include <iostream>
#include <string>

inline void CheckOpenGLError(std::string const& errorMsg) {
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
  }
}