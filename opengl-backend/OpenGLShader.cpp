#include "OpenGLShader.hpp"
#include "OpenGLHeaders.h"
#include <iostream>

using std::cout;

OpenGLShader::OpenGLShader() { initializeMembers(); }

OpenGLShader::~OpenGLShader() {
  glDeleteProgram(m_id);
  CheckOpenGLError("glDeleteProgram");
  initializeMembers();
}

Shader& OpenGLShader::use() {
  glUseProgram(m_id);
  CheckOpenGLError("glUseProgram");
  return *this;
}

void OpenGLShader::load(string const& vertexSource,
                        string const& fragmentSource) {
  unsigned int sVertex, sFragment;
  // vertex Shader
  char const* vertexSourceCStr = vertexSource.c_str();
  sVertex = glCreateShader(GL_VERTEX_SHADER);
  CheckOpenGLError("glCreateShader");
  glShaderSource(sVertex, 1, &vertexSourceCStr, NULL);
  CheckOpenGLError("glShaderSource");
  glCompileShader(sVertex);
  CheckOpenGLError("glCompileShader");
  checkCompileErrors(sVertex, "VERTEX");

  // fragment Shader
  char const* fragmentSourceCStr = fragmentSource.c_str();
  sFragment = glCreateShader(GL_FRAGMENT_SHADER);
  CheckOpenGLError("glCreateShader");
  glShaderSource(sFragment, 1, &fragmentSourceCStr, NULL);
  CheckOpenGLError("glShaderSource");
  glCompileShader(sFragment);
  CheckOpenGLError("glCompileShader");
  checkCompileErrors(sFragment, "FRAGMENT");

  // shader program
  m_id = glCreateProgram();
  CheckOpenGLError("glCreateProgram");
  glAttachShader(m_id, sVertex);
  CheckOpenGLError("glAttachShader");
  glAttachShader(m_id, sFragment);
  CheckOpenGLError("glAttachShader");
  glLinkProgram(m_id);
  CheckOpenGLError("glLinkProgram");
  checkCompileErrors(m_id, "PROGRAM");

  // delete the shaders as they're linked into our program now and no longer
  // necessary
  glDeleteShader(sVertex);
  CheckOpenGLError("glDeleteShader");
  glDeleteShader(sFragment);
  CheckOpenGLError("glDeleteShader");
}

void OpenGLShader::setFloat(string const& name, float value) {
  glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
  CheckOpenGLError("glUniform1f");
}

void OpenGLShader::setInteger(string const& name, int value) {
  glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
  CheckOpenGLError("glUniform1i");
}

void OpenGLShader::setVector2f(string const& name, glm::vec2 const& value) {
  glUniform2f(glGetUniformLocation(m_id, name.c_str()), value.x, value.y);
  CheckOpenGLError("glUniform2f");
}

void OpenGLShader::setVector3f(string const& name, glm::vec3 const& value) {
  glUniform3f(glGetUniformLocation(m_id, name.c_str()), value.x, value.y,
              value.z);
  CheckOpenGLError("glUniform3f");
}

void OpenGLShader::setVector4f(string const& name, glm::vec4 const& value) {
  glUniform4f(glGetUniformLocation(m_id, name.c_str()), value.x, value.y,
              value.z, value.w);
  CheckOpenGLError("glUniform4f");
}

void OpenGLShader::setMatrix4(string const& name, glm::mat4 const& matrix) {
  glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, false,
                     glm::value_ptr(matrix));
  CheckOpenGLError("glUniformMatrix4fv");
}

void OpenGLShader::checkCompileErrors(unsigned int object, string const& type) {
  int success;
  char infoLog[1024];
  if (type != "PROGRAM") {
    glGetShaderiv(object, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(object, 1024, NULL, infoLog);
      cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
           << infoLog
           << "\n -- --------------------------------------------------- -- "
           << std::endl;
    }
  } else {
    glGetProgramiv(object, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(object, 1024, NULL, infoLog);
      cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
           << infoLog
           << "\n -- --------------------------------------------------- -- "
           << std::endl;
    }
  }
}