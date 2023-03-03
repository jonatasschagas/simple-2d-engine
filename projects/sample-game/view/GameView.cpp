#include "GameView.hpp"

GameView::GameView(
                    PlatformManager& rPlatformManager, 
                    DataCacheManager& rDataCacheManager
                ) : View(&rPlatformManager),
                m_rPlatformManager(rPlatformManager),
                m_rDataCacheManager(rDataCacheManager),
                m_characterSprite(&rPlatformManager, rDataCacheManager, "assets/characters/virtual-guy_animation.json")
{
}

GameView::~GameView(){}

void GameView::initialize(ViewManager* pViewManager)
{
    addChild(&m_characterSprite);
    m_characterSprite.setPosition(Vector2(10, 10));
    m_characterSprite.setSize(Vector2(10, 10));
    m_characterSprite.play("run");
}

void GameView::receiveEvent(Event* pEvent)
{

}

void GameView::readInput(int x, int y, bool pressed)
{

}

void GameView::updateEditor()
{

}