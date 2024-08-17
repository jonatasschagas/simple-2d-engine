#pragma once
#ifndef GraphicsManager_h
#define GraphicsManager_h

#include "Shader.hpp"
#include "disk/ResourceProvider.hpp"
#include <glm/glm.hpp>
#include <string>

using std::string;

struct Texture {
  string texturePath;
  int width;
  int height;
};

/**
 * GraphicsManager is an abstract class that defines the interface for
 * graphics-related functionality. It is used by the Engine to render
 * textures to the screen.
 */
class GraphicsManager {
 public:
  virtual ~GraphicsManager() {}

  /**
   * initialize is called by the Engine when it is first initialized.
   */
  virtual void initialize() {};

  /**
   * loadShader is called by the Engine when it needs to load a shader from
   * disk.
   * @param shaderName the name of the shader
   * @param vertexPath the path to the vertex shader
   * @param fragmentPath the path to the fragment shader
   * @param rResourceProvider the ResourceProvider to use to load the shaders
   */
  virtual void loadShader(string const& shaderName, string const& vertexPath,
                          string const& fragmentPath,
                          ResourceProvider& rResourceProvider) = 0;

  /**
   * getShader is called by the Engine when it needs to get a shader.
   * @param shaderName the name of the shader
   * @return a reference to the Shader
   */
  virtual Shader& getShader(string const& shaderName) = 0;

  /**
   * renderTexture is called by the Engine when a texture needs to be
   * rendered to the screen.
   *
   * @param transform the transformation matrix to apply to the texture
   * @param textureCoordinates the texture coordinates to apply to the
   * texture
   * @param texturePath the path to the texture to render
   * @param rShader the shader to use to render the texture
   */
  virtual void renderTexture(glm::mat4 const& transform,
                             glm::vec4 const& textureCoordinates,
                             string const& texturePath, Shader& rShader) = 0;

  /**
   * renderColoredSprite is called by the Engine when a colored sprite
   * @param transform the transformation matrix to apply to the sprite
   * @param rShader the shader to use to render the sprite
   */
  virtual void renderColoredSprite(glm::mat4 const& transform,
                                   Shader& rShader) = 0;

  /**
   * loadTexture is called by the Engine when a texture needs to be
   * loaded from disk into the graphics system.
   * @param path the path to the texture to load
   * @return Texture
   */
  virtual Texture loadTexture(string const& path) = 0;

  /**
   * getWorldLocationXFromScreenCoordinates is called by the Engine when
   * it needs to convert a screen coordinate to a world coordinate.
   * @param x the screen coordinate to convert
   * @return the world coordinate
   */
  virtual int const getWorldLocationXFromScreenCoordinates(int x) const = 0;

  /**
   * getWorldLocationYFromScreenCoordinates is called by the Engine when
   * it needs to convert a screen coordinate to a world coordinate.
   * @param y the screen coordinate to convert
   * @return the world coordinate
   */
  virtual int const getWorldLocationYFromScreenCoordinates(int y) const = 0;

  /**
   * getScreenSizeInGameUnits is called by the Engine when it needs to
   * know the size of the screen in game units.
   * @return the size of the screen in game units
   */
  virtual glm::vec2 const getScreenSizeInGameUnits() const = 0;

  /**
   * getScreenWidth is called by the Engine when it needs to know the
   * width of the screen.
   * @return the width of the screen
   */
  virtual int getScreenWidth() const = 0;

  /**
   * getScreenHeight is called by the Engine when it needs to know the
   * height of the screen.
   * @return the height of the screen
   */
  virtual int getScreenHeight() const = 0;

  /**
   * getScaleFactor is called by the Engine when it needs to know the
   * scale factor of the screen.
   * @param x the x scale factor
   * @param y the y scale factor
   * @return the scale factor of the screen
   */
  virtual void getScaleFactor(float& x, float& y) const = 0;
};

#endif /* GraphicsManager_h */
