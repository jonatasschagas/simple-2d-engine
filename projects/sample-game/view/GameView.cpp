#include "GameView.hpp"
#include "core/SpriteFactory.hpp"

GameView::GameView()
    : View(),
      m_characterSprite(SpriteFactory::buildAnimatedSprite(
          "assets/characters/virtual-guy_animation.json")) {}

GameView::~GameView() {}

void GameView::initialize(ViewManager* pViewManager) {
  addChild(&m_characterSprite);
  m_characterSprite.setXY(10, 10);
  m_characterSprite.setSize(10, 10);
  m_characterSprite.play("run");
}

void GameView::receiveEvent(Event* pEvent) {}

void GameView::readInput(int x, int y, bool pressed) {}

void GameView::updateEditor() {}