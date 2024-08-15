#include "Shader.hpp"
#include "OpenGLHeaders.h"
#include <iostream>

Shader::Shader() { initializeMembers(); }

Shader::~Shader() {
  glDeleteProgram(m_id);
  initializeMembers();
}

Shader& Shader::use() {
  glUseProgram(m_id);
  return *this;
}

void Shader::compile(string const& vertexSource, string const& fragmentSource) {
  unsigned int sVertex, sFragment;
  // vertex Shader
  char const* vertexSourceCStr = vertexSource.c_str();
  sVertex = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(sVertex, 1, &vertexSourceCStr, NULL);
  glCompileShader(sVertex);
  checkCompileErrors(sVertex, "VERTEX");

  // fragment Shader
  char const* fragmentSourceCStr = fragmentSource.c_str();
  sFragment = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(sFragment, 1, &fragmentSourceCStr, NULL);
  glCompileShader(sFragment);
  checkCompileErrors(sFragment, "FRAGMENT");

  // shader program
  m_id = glCreateProgram();
  glAttachShader(m_id, sVertex);
  glAttachShader(m_id, sFragment);
  glLinkProgram(m_id);
  checkCompileErrors(m_id, "PROGRAM");

  // delete the shaders as they're linked into our program now and no longer
  // necessary
  glDeleteShader(sVertex);
  glDeleteShader(sFragment);
}

void Shader::setFloat(string const& name, float value) {
  glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::setInteger(string const& name, int value) {
  glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::setVector2f(string const& name, float x, float y) {
  glUniform2f(glGetUniformLocation(m_id, name.c_str()), x, y);
}

void Shader::setVector2f(string const& name, glm::vec2 const& value) {
  glUniform2f(glGetUniformLocation(m_id, name.c_str()), value.x, value.y);
}

void Shader::setVector3f(string const& name, float x, float y, float z) {
  glUniform3f(glGetUniformLocation(m_id, name.c_str()), x, y, z);
}

void Shader::setVector3f(string const& name, glm::vec3 const& value) {
  glUniform3f(glGetUniformLocation(m_id, name.c_str()), value.x, value.y,
              value.z);
}

void Shader::setVector4f(string const& name, float x, float y, float z,
                         float w) {
  glUniform4f(glGetUniformLocation(m_id, name.c_str()), x, y, z, w);
}

void Shader::setVector4f(string const& name, glm::vec4 const& value) {
  glUniform4f(glGetUniformLocation(m_id, name.c_str()), value.x, value.y,
              value.z, value.w);
}

void Shader::setMatrix4(string const& name, glm::mat4 const& matrix) {
  glUniformMatrix4fv(glGetUniformLocation(m_id, name.c_str()), 1, false,
                     glm::value_ptr(matrix));
}

void Shader::checkCompileErrors(unsigned int object, string const& type) {
  int success;
  char infoLog[1024];
  if (type != "PROGRAM") {
    glGetShaderiv(object, GL_COMPILE_STATUS, &success);
    if (!success) {
      glGetShaderInfoLog(object, 1024, NULL, infoLog);
      cout << "| ERROR::SHADER: Compile-time error: Type: " << type << "\n"
           << infoLog
           << "\n -- --------------------------------------------------- -- "
           << endl;
    }
  } else {
    glGetProgramiv(object, GL_LINK_STATUS, &success);
    if (!success) {
      glGetProgramInfoLog(object, 1024, NULL, infoLog);
      cout << "| ERROR::Shader: Link-time error: Type: " << type << "\n"
           << infoLog
           << "\n -- --------------------------------------------------- -- "
           << endl;
    }
  }
}