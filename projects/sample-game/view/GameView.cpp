#include "GameView.hpp"
#include "core/SpriteFactory.hpp"
#include <memory>

GameView::GameView(GraphicsManager& rGraphicsManager) : View(), m_rGraphicsManager(rGraphicsManager), m_head("assets/planets/planet00.png", 0.01f, this) {}

GameView::~GameView() {}

void GameView::initialize(ViewManager* pViewManager) {
  
  addChild(&m_head);
  m_head.setSize(10.f, 10.f);
  m_head.setXY(1, 1);
}

void GameView::update(float delta) {
  Sprite::update(delta);
}

bool GameView::canMoveRight(float x) const {
  return x < getWidth();
}

bool GameView::canMoveLeft(float x) const {
  return x > 0;
}

bool GameView::canMoveUp(float y) const {
  return y > 0;
}

bool GameView::canMoveDown(float y) const {
  return y < getHeight();
}

void GameView::receiveEvent(Event* pEvent) {
  if (pEvent->getName().find("right-end") != std::string::npos) {
    m_head.setDirection(Head::Direction::RIGHT);
  } else if (pEvent->getName().find("left-end") != std::string::npos) {
    m_head.setDirection(Head::Direction::LEFT);
  } else if (pEvent->getName().find("up-end") != std::string::npos) {
    m_head.setDirection(Head::Direction::UP);
  } else if (pEvent->getName().find("down-end") != std::string::npos) {
    m_head.setDirection(Head::Direction::DOWN);
  }
}

void GameView::readInput(int x, int y, bool pressed) {}

void GameView::updateEditor() {}
