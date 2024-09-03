#pragma once
#ifndef ViewManager_hpp
#define ViewManager_hpp

#include "View.h"
#include "disk/ResourceProvider.hpp"
#include "graphics/GraphicsManager.hpp"
#include "input/InputManager.hpp"
#include "sound/SoundManager.hpp"
#include <map>
#include <stdio.h>
#include <string>
#include <vector>

using std::map;
using std::string;

class ViewManager {
 public:
  ViewManager(glm::vec2 screenSizeInGameUnits, InputManager& rInputManager,
              ResourceProvider& rResourceProvider);
  ~ViewManager();

  void render(GraphicsManager& rGraphicsManager);

  void processSounds(SoundManager& rSoundManager);

  void update(float delta);

  void addView(string const& viewName, View* pView);

  void switchView(string const& viewName);

  glm::vec2 const& getScreenSizeInGameUnits() const {
    return m_screenSizeInGameUnits;
  }

  ResourceProvider& getResourceProvider() { return m_rResourceProvider; }

 private:
  glm::vec2 m_screenSizeInGameUnits;
  View* m_pCurrentView;
  View* m_pPreviousView;

  map<string, View*> m_views;
  InputManager& m_rInputManager;
  ResourceProvider& m_rResourceProvider;

  void initializeMembers() {
    m_pCurrentView = nullptr;
    m_pPreviousView = nullptr;
    m_views.clear();
  }
};

#endif /* ViewManager_hpp */
