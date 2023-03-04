#pragma once
#ifndef Shader_hpp
#define Shader_hpp

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

using namespace std;

class Shader {
 public:
  Shader();
  ~Shader();

  Shader& use();

  void compile(string const& vertexSource, string const& fragmentSource);

  void setFloat(string const& name, float value);
  void setInteger(string const& name, int value);
  void setVector2f(string const& name, float x, float y);
  void setVector2f(string const& name, glm::vec2 const& value);
  void setVector3f(string const& name, float x, float y, float z);
  void setVector3f(string const& name, glm::vec3 const& value);
  void setVector4f(string const& name, float x, float y, float z, float w);
  void setVector4f(string const& name, glm::vec4 const& value);
  void setMatrix4(string const& name, glm::mat4 const& matrix);

  unsigned int id() const { return m_id; }

 private:
  void checkCompileErrors(unsigned int object, string const& type);

  unsigned int m_id;

  void initializeMembers() { m_id = 0; }
};

#endif /* Shader_hpp */