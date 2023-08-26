#pragma once
#ifndef GameView_hpp
#define GameView_hpp

#include "platform/GraphicsManager.hpp"
#include "view/View.h"
#include "Earth.hpp"

class GameView : public View {
 public:
  GameView(GraphicsManager& rGraphicsManager);
  ~GameView();

  void initialize(ViewManager* pViewManager) override;
  virtual void receiveEvent(Event* pEvent) override;
  virtual void readInput(int x, int y, bool pressed) override;
  virtual void updateEditor() override;

 private:
    GraphicsManager& m_rGraphicsManager;
    Earth m_earth;
};

#endif /* GameView_hpp */
