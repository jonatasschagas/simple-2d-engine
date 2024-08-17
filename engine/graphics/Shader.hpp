#pragma once
#ifndef Shader_hpp
#define Shader_hpp

#include <glm/glm.hpp>
#include <string>

using std::string;

/**
 * Shader is an abstract class that defines the interface for
 * shader-related functionality. It is used by the Engine to render
 * textures to the screen.
 * @ingroup graphics
 */
class Shader {
 public:
  /**
   * load is called by the Engine when it needs to load a shader from disk.
   * @param vertexSourceCode the source code of the vertex shader
   * @param fragmentSourceCode the source code of the fragment shader
   */
  virtual void load(string const& vertexSourceCode,
                    string const& fragmentSourceCode) = 0;

  /**
   * use is called by the Engine when it needs to use the shader.
   * @return a reference to the Shader
   */
  virtual Shader& use() = 0;

  /**
   * setFloat is called by the Engine when it needs to set a float uniform
   * in the shader.
   * @param name the name of the uniform
   * @param value the value to set the uniform to
   */
  virtual void setFloat(string const& name, float value) = 0;

  /**
   * setInteger is called by the Engine when it needs to set an integer uniform
   * in the shader.
   * @param name the name of the uniform
   * @param value the value to set the uniform to
   */
  virtual void setInteger(string const& name, int value) = 0;

  /**
   * setVector2f is called by the Engine when it needs to set a vec2 uniform
   * in the shader.
   * @param name the name of the uniform
   * @param value the value to set the uniform to
   */
  virtual void setVector2f(string const& name, glm::vec2 const& value) = 0;

  /**
   * setVector2f is called by the Engine when it needs to set a vec2 uniform
   * in the shader.
   * @param name the name of the uniform
   * @param x the x value of the vec2
   * @param y the y value of the vec2
   */
  virtual void setVector3f(string const& name, glm::vec3 const& value) = 0;

  /**
   * setVector3f is called by the Engine when it needs to set a vec3 uniform
   * in the shader.
   * @param name the name of the uniform
   * @param x the x value of the vec3
   * @param y the y value of the vec3
   * @param z the z value of the vec3
   */
  virtual void setVector4f(string const& name, glm::vec4 const& value) = 0;

  /**
   * setVector4f is called by the Engine when it needs to set a vec4 uniform
   * in the shader.
   * @param name the name of the uniform
   * @param x the x value of the vec4
   * @param y the y value of the vec4
   * @param z the z value of the vec4
   * @param w the w value of the vec4
   */
  virtual void setMatrix4(string const& name, glm::mat4 const& matrix) = 0;
};

#endif /* Shader_hpp */