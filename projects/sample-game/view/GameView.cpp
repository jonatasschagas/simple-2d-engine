#include "GameView.hpp"

GameView::GameView(GraphicsManager& rGraphicsManager)
    : View(),
      m_rGraphicsManager(rGraphicsManager),
      m_starField(300, 0.05f),
      m_rocket(0.01f),
      m_rotatingPlanet(0.01f, "assets/images/planet01.png", 5.0f, 5.0f, 0.1f,
                       0.1f, true) {}

GameView::~GameView() {}

void GameView::initialize(ViewManager* pViewManager) {
  setColor(0, 0, 0, 255);

  addChild(&m_starField);
  addChild(&m_rocket);

  m_rocket.setXY(5.f, 0.5f);
  m_rocket.setSize(0.1f, 0.18f);

  m_rotatingPlanet.setWholeTexture(true);
  addChild(&m_rotatingPlanet);
}

void GameView::receiveEvent(Event* pEvent) {}

void GameView::readInput(int x, int y, bool pressed) {}

void GameView::updateEditor() {}

void GameView::update(float delta) { Sprite::update(delta); }