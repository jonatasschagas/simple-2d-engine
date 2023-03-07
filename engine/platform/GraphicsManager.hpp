#pragma once
#ifndef GraphicsManager_h
#define GraphicsManager_h

#include "DrawCall.h"

/**
 * GraphicsManager is an abstract class that defines the interface for
 * graphics-related functionality. It is used by the Engine to render
 * textures to the screen.
 */
class GraphicsManager {
 public:
  /**
   * initialize is called by the Engine when it is first initialized.
   */
  virtual void initialize(){};

  /**
   * setOffsetY is called by the Engine when the camera is moved.
   * @param x the new x offset of the camera
   * @param y the new y offset of the camera
   */
  virtual void setOffset(float x, float y) = 0;

  /**
   * renderTexture is called by the Engine when a texture needs to be
   * rendered to the screen.
   * @param drawCall the DrawCall containing the texture to render
   */
  virtual void renderTexture(DrawCall const& drawCall) = 0;

  /**
   * loadTexture is called by the Engine when a texture needs to be
   * loaded from disk into the graphics system.
   * @param path the path to the texture to load
   * @return a pointer to the loaded texture
   */
  virtual void* loadTexture(string const& path) = 0;

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
  virtual const Vector2 getScreenSizeInGameUnits() const = 0;

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

  virtual ~GraphicsManager() {}
};

#endif /* GraphicsManager_h */