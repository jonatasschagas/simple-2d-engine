#pragma once
#ifndef GameView_hpp
#define GameView_hpp

#include "objects/Rocket.hpp"
#include "objects/RotatingPlanet.hpp"
#include "objects/StarField.hpp"
#include "platform/GraphicsManager.hpp"
#include "view/View.h"
#include <vector>

class GameView : public View {
 public:
  GameView(GraphicsManager& rGraphicsManager);
  ~GameView();

  void initialize(ViewManager* pViewManager) override;
  virtual void receiveEvent(Event* pEvent) override;
  virtual void readInput(int x, int y, bool pressed) override;
  virtual void updateEditor() override;

  void update(float delta) override;

 private:
  GraphicsManager& m_rGraphicsManager;

  StarField m_starField;
  Rocket m_rocket;
  RotatingPlanet m_rotatingPlanet;
};

#endif /* GameView_hpp */
