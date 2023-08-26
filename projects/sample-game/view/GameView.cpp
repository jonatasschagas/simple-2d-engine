#include "GameView.hpp"
#include "core/SpriteFactory.hpp"
#include <memory>

GameView::GameView(GraphicsManager& rGraphicsManager) : View(), m_rGraphicsManager(rGraphicsManager){}

GameView::~GameView() {}

void GameView::initialize(ViewManager* pViewManager) {
  loadTexture("assets/images/mountain-cartoony.png");
  useFullTexture();
  
  addChild(&m_earth);
}

void GameView::receiveEvent(Event* pEvent) {
  /*if (pEvent->getName().find("right") != std::string::npos) {
    m_tileMapSprite.setXY(m_tileMapSprite.getX() + 1, m_tileMapSprite.getY());
  } else if (pEvent->getName().find("left") != std::string::npos) {
    m_tileMapSprite.setXY(m_tileMapSprite.getX() - 1, m_tileMapSprite.getY());
  } else if (pEvent->getName().find("up") != std::string::npos) {
    m_tileMapSprite.setXY(m_tileMapSprite.getX(), m_tileMapSprite.getY() - 1);
  } else if (pEvent->getName().find("down") != std::string::npos) {
    m_tileMapSprite.setXY(m_tileMapSprite.getX(), m_tileMapSprite.getY() + 1);
  }*/
}

void GameView::readInput(int x, int y, bool pressed) {}

void GameView::updateEditor() {}
