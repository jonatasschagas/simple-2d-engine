#include "GameView.hpp"
#include "input/InputKey.hpp"

GameView::GameView() : View(), m_starField(300, 0.001f), m_rocket(0.01f) {}

GameView::~GameView() {}

void GameView::initialize(ViewManager* pViewManager) {
  addChild(&m_starField);
  addChild(&m_rocket);

  m_starField.setXY(0, 0);
  m_starField.setSize(100.f, 100.f);

  m_rocket.setXY(25.f, 50.f);
  m_rocket.setSize(10.f, 15.f);
}

void GameView::update(float delta) { StructuralSprite::update(delta); }

void GameView::onKeyPressed(InputKey key) {
  switch (key) {
    case InputKey::KEY_UP:
      m_rocket.moveUp();
      break;
    case InputKey::KEY_DOWN:
      m_rocket.moveDown();
      break;
    case InputKey::KEY_LEFT:
      m_rocket.moveLeft();
      break;
    case InputKey::KEY_RIGHT:
      m_rocket.moveRight();
      break;
    default:
      break;
  }
}