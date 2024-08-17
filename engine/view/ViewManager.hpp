#pragma once
#ifndef ViewManager_hpp
#define ViewManager_hpp

#include "View.h"
#include "event/EventListener.hpp"
#include "graphics/GraphicsManager.hpp"
#include "sound/SoundManager.hpp"
#include <map>
#include <stdio.h>
#include <string>
#include <vector>

using std::map;
using std::string;

class ViewManager : public EventListener {
 public:
  ViewManager(glm::vec2 screenSizeInGameUnits);
  ~ViewManager();

  void receiveEvent(Event* pEvent) override;
  void render(GraphicsManager& rGraphicsManager);
  void processSounds(SoundManager& rSoundManager);
  void readInput(int x, int y, bool pressed);
  void update(float delta);

  void updateEditor();

  void addView(string const& viewName, View* pView);
  void switchView(string const& viewName);

  glm::vec2 const& getScreenSizeInGameUnits() const {
    return m_screenSizeInGameUnits;
  }

 private:
  glm::vec2 m_screenSizeInGameUnits;
  View* m_pCurrentView;
  View* m_pPreviousView;

  map<string, View*> m_views;

  void initializeMembers() {
    m_pCurrentView = nullptr;
    m_pPreviousView = nullptr;
    m_views.clear();
  }
};

#endif /* ViewManager_hpp */
