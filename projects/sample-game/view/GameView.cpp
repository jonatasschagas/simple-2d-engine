#include "GameView.hpp"
#include "core/SpriteFactory.hpp"
#include <memory>

GameView::GameView()
    : View(),
      m_characterSprite(SpriteFactory::buildAnimatedSprite(
          "assets/characters/virtual-guy_animation.json")),
      m_tileMapSprite(SpriteFactory::buildTileMapSprite(
          "assets/levels/menu.json", "assets/levels", "assets/levels",
          Vector2(5, 5), "meta")) {}

GameView::~GameView() {}

void GameView::initialize(ViewManager* pViewManager) {
  addChild(&m_tileMapSprite);
  m_tileMapSprite.fillParent();
  m_tileMapSprite.setXY(0, 0);
  m_tileMapSprite.setDisableCamera(true);
  addChild(&m_characterSprite);
  m_characterSprite.setXY(10, 10);
  m_characterSprite.setSize(10, 10);
  m_characterSprite.play("run");
}

void GameView::receiveEvent(Event* pEvent) {
  if (pEvent->getName() == "right") {
    m_tileMapSprite.setXY(m_tileMapSprite.getX() + 1, m_tileMapSprite.getY());
  } else if (pEvent->getName() == "left") {
    m_tileMapSprite.setXY(m_tileMapSprite.getX() - 1, m_tileMapSprite.getY());
  } else if (pEvent->getName() == "up") {
    m_tileMapSprite.setXY(m_tileMapSprite.getX(), m_tileMapSprite.getY() - 1);
  } else if (pEvent->getName() == "down") {
    m_tileMapSprite.setXY(m_tileMapSprite.getX(), m_tileMapSprite.getY() + 1);
  }
}

void GameView::readInput(int x, int y, bool pressed) {}

void GameView::updateEditor() {}