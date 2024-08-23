#pragma once
#ifndef GLFWInputManager_hpp
#define GLFWInputManager_hpp

#include "input/InputManager.hpp"
#include <GLFW/glfw3.h>
#include <functional>

class GLFWInputManager : public InputManager {
 public:
  GLFWInputManager(GLFWwindow& rWindow);

  ~GLFWInputManager();

  virtual void pollEvents() override;

  /** Set the function to translate GLFW key codes to InputKey values */
  void setKeyTranslatorFunction(
      std::function<InputKey(int)> keyTranslatorFunction) {
    m_keyTranslatorFunction = keyTranslatorFunction;
  }

 private:
  GLFWwindow& m_rWindow;

  std::function<InputKey(int)> m_keyTranslatorFunction;
};

#endif /* GLFWInputManager_hpp */
