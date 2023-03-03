#include "SampleGame.hpp"

#include "view/GameView.hpp"
#include <glm/glm.hpp>

SampleGame::SampleGame() : Game()
{
    initializeMembers();
}

SampleGame::~SampleGame()
{
    initializeMembers();
}

void SampleGame::initialize(PlatformManager* pManager)
{
    pManager->initialize();

    m_gameName = "Sample Game";
    m_pPlatformManager = pManager;
    m_viewManager = ViewManager();
    m_viewManager.initialize(m_pPlatformManager, &m_dataCacheManager);

    GameView* pGameView = new GameView(*m_pPlatformManager, m_dataCacheManager);
    m_viewManager.addView("game-view", pGameView);
    m_viewManager.switchView("game-view");
}

void SampleGame::receiveEvent(Event* pEvent)
{

}

void SampleGame::update(const float deltaTime)
{
    m_viewManager.update(deltaTime);
}

void SampleGame::updateEditor(const float deltaTime)
{

}

void SampleGame::render()
{
    m_viewManager.render();
}

const string& SampleGame::getGameName()
{
    return m_gameName;
}
