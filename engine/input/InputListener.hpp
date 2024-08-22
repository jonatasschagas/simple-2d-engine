#pragma once
#ifndef InputListener_h
#define InputListener_h

#include "InputKey.hpp"

/**
 * InputListener is an abstract class that defines the interface for
 * input-related functionality. It is used by the Engine to handle
 * input from the user and notify the game when input events occur.
 */
class InputListener {
 public:
  virtual ~InputListener() {}

  /**
   * onKeyPressed is called by the Engine when a key is pressed.
   * @param key the key that was pressed
   */
  virtual void onKeyPressed(InputKey key) {};

  /**
   * onKeyReleased is called by the Engine when a key is released.
   * @param key the key that was released
   */
  virtual void onKeyReleased(InputKey key) {};

  /**
   * onMouseMoved is called by the Engine when the mouse is moved.
   * @param x the x coordinate of the mouse
   * @param y the y coordinate of the mouse
   */
  virtual void onMouseMoved(int x, int y) {};

  /**
   * onMousePressed (also touches) is called by the Engine when the mouse is
   * pressed.
   * @param x the x coordinate of the mouse
   * @param y the y coordinate of the mouse
   */
  virtual void onMousePressed(int x, int y) {};

  /**
   * onMouseReleased (also touches) is called by the Engine when the mouse is
   * released.
   * @param x the x coordinate of the mouse
   * @param y the y coordinate of the mouse
   */
  virtual void onMouseReleased(int x, int y) {};
};

#endif /* InputListener_h */