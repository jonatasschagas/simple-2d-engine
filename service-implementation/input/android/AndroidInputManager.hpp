#pragma once
#ifndef AndroidInputManager_hpp
#define AndroidInputManager_hpp

#include "input/InputManager.hpp"
struct android_app;

class AndroidInputManager : public InputManager {
 public:
  AndroidInputManager(android_app* pApp);

  ~AndroidInputManager();

  virtual void pollEvents() override;

 private:
  android_app* m_pApp = nullptr;
  InputListener* m_pInputListener = nullptr;
};

#endif /* AndroidInputManager_hpp */
