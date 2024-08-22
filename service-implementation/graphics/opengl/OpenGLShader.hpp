#pragma once
#ifndef OpenGLShader_hpp
#define OpenGLShader_hpp

#include "OpenGLHeaders.h"
#include "graphics/Shader.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

using std::string;

class OpenGLShader : public Shader {
 public:
  OpenGLShader();
  ~OpenGLShader();

  Shader& use() override;

  void load(string const& vertexSourceCode,
            string const& fragmentSourceCode) override;

  void setFloat(string const& name, float value) override;
  void setInteger(string const& name, int value) override;
  void setVector2f(string const& name, glm::vec2 const& value) override;
  void setVector3f(string const& name, glm::vec3 const& value) override;
  void setVector4f(string const& name, glm::vec4 const& value) override;
  void setMatrix4(string const& name, glm::mat4 const& matrix) override;

  unsigned int getId() const { return m_id; }

 private:
  void checkCompileErrors(unsigned int object, string const& type);

  unsigned int m_id = 0;

  void initializeMembers() { m_id = 0; }
};

#endif /* OpenGLShader */