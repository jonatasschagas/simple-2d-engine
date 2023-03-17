#pragma once
#ifndef ViewManager_hpp
#define ViewManager_hpp

#include "View.h"
#include "event/EventListener.hpp"
#include "platform/GraphicsManager.hpp"
#include "platform/SoundManager.hpp"
#include <map>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

class ViewManager : public EventListener {
 public:
  ViewManager(Vector2 const& screenSizeInGameUnits);
  ~ViewManager();

  void receiveEvent(Event* pEvent) override;
  void render(GraphicsManager& rGraphicsManager);
  void processSounds(SoundManager& rSoundManager);
  void readInput(int x, int y, bool pressed);
  void update(float delta);

  void updateEditor();

  void addView(string const& viewName, View* pView);
  void switchView(string const& viewName);

 private:
  Vector2 m_screenSizeInGameUnits;
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
