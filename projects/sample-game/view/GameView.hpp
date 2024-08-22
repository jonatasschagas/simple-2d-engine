#pragma once
#ifndef GameView_hpp
#define GameView_hpp

#include "objects/Rocket.hpp"
#include "objects/StarField.hpp"
#include "view/View.h"
#include <vector>

class GameView : public View {
 public:
  GameView();
  ~GameView();

  void initialize(ViewManager* pViewManager) override;

  void update(float delta) override;

  void onKeyPressed(InputKey key) override;

 private:
  StarField m_starField;
  Rocket m_rocket;
};

#endif /* GameView_hpp */
