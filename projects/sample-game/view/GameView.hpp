#pragma once
#ifndef GameView_hpp
#define GameView_hpp

#include "platform/GraphicsManager.hpp"
#include "view/View.h"
#include "Maze.hpp"
#include "Head.hpp"
#include <vector>

class GameView : public View, public Maze {
public:
  GameView(GraphicsManager& rGraphicsManager);
  ~GameView();

  void initialize(ViewManager* pViewManager) override;
  virtual void receiveEvent(Event* pEvent) override;
  virtual void readInput(int x, int y, bool pressed) override;
  virtual void updateEditor() override;

  virtual bool canMoveRight(float x) const override;
  virtual bool canMoveLeft(float x) const override;
  virtual bool canMoveUp(float y) const override;
  virtual bool canMoveDown(float y) const override;
  
  void update(float delta) override;
  
private:

  GraphicsManager& m_rGraphicsManager;
  
  Head m_head;

};

#endif /* GameView_hpp */
