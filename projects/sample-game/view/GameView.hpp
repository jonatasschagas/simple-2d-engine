#pragma once
#ifndef GameView_hpp
#define GameView_hpp

#include "core/AnimatedSprite.hpp"
#include "data/DataCacheManager.hpp"
#include "view/View.h"

class GameView : public View {
 public:
  GameView();
  ~GameView();

  void initialize(ViewManager* pViewManager) override;
  virtual void receiveEvent(Event* pEvent) override;
  virtual void readInput(int x, int y, bool pressed) override;
  virtual void updateEditor() override;

 private:
  AnimatedSprite m_characterSprite;
};

#endif /* GameView_hpp */