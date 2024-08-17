#include "GameView.hpp"

GameView::GameView(GraphicsManager& rGraphicsManager)
    : View(),
      m_rGraphicsManager(rGraphicsManager),
      m_starField(300, 0.001f),
      m_rocket(0.01f) {}

GameView::~GameView() {}

void GameView::initialize(ViewManager* pViewManager) {
  addChild(&m_starField);
  addChild(&m_rocket);

  m_starField.setXY(0, 0);
  m_starField.setSize(100.f, 100.f);

  m_rocket.setXY(25.f, 50.f);
  m_rocket.setSize(10.f, 15.f);
}

void GameView::receiveEvent(Event* pEvent) {}

void GameView::readInput(int x, int y, bool pressed) {}

void GameView::updateEditor() {}

void GameView::update(float delta) { StructuralSprite::update(delta); }