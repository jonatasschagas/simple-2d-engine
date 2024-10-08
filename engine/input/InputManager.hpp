#pragma once
#ifndef InputManager_h
#define InputManager_h

#include "InputListener.hpp"

/**
 * InputManager is an abstract class that defines the interface for
 * for input-related functionality. It is used by the Engine to handle
 * input from the user.
 */
class InputManager {
 public:
  virtual ~InputManager() {}

  /**
   * setListener is called by the Engine to set the InputListener to use
   * @param pInputListener the InputListener to use for input events
   */
  void setListener(InputListener* pInputListener) {
    m_pInputListener = pInputListener;
  }

  /**
   * pollEvents is called by the Engine when it needs to poll for input events.
   */
  virtual void pollEvents() = 0;

 protected:
  InputListener* m_pInputListener = nullptr;
};

#endif /* InputManager_h */
