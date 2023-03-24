#pragma once
#ifndef GameView_hpp
#define GameView_hpp

#include "core/AnimatedSprite.hpp"
#include "core/TileMapSprite.hpp"
#include "data/DataCacheManager.hpp"
#include "platform/GraphicsManager.hpp"
#include "view/View.h"

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
  AnimatedSprite m_characterSprite;
  TileMapSprite m_tileMapSprite;
};

#endif /* GameView_hpp */