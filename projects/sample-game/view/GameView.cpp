#include "GameView.hpp"

GameView::GameView(GraphicsManager& rGraphicsManager)
    : View(),
      m_rGraphicsManager(rGraphicsManager),
      m_starField(300, 0.001f),
      m_rocket(0.01f) {}

GameView::~GameView() {}

void GameView::initialize(ViewManager* pViewManager) {
  setColor(0, 0, 0, 255);

  addChild(&m_starField);
  addChild(&m_rocket);

  m_rocket.setXY(.4f, .5f);
  m_rocket.setSize(0.1f, 0.15f);
}

void GameView::receiveEvent(Event* pEvent) {}

void GameView::readInput(int x, int y, bool pressed) {}

void GameView::updateEditor() {}

void GameView::update(float delta) { Sprite::update(delta); }