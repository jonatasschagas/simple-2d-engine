#include "SampleGame.hpp"
#include "view/GameView.hpp"
#include <glm/glm.hpp>

SampleGame::SampleGame(GraphicsManager& rGraphicsManager,
                       SoundManager& rSoundManager)
    : Game(rGraphicsManager, rSoundManager),
      m_viewManager(rGraphicsManager.getScreenSizeInGameUnits()) {
  initializeMembers();
}

SampleGame::~SampleGame() { initializeMembers(); }

void SampleGame::initialize() {
  m_viewManager = ViewManager(m_rGraphicsManager.getScreenSizeInGameUnits());

  GameView* pGameView = new GameView(m_rGraphicsManager);
  m_viewManager.addView("game-view", pGameView);
  m_viewManager.switchView("game-view");
}

void SampleGame::receiveEvent(Event* pEvent) {
  m_viewManager.receiveEvent(pEvent);
}

void SampleGame::update(float const deltaTime) {
  m_viewManager.update(deltaTime);
}

void SampleGame::updateEditor(float const deltaTime) {}

void SampleGame::render() { m_viewManager.render(m_rGraphicsManager); }

void SampleGame::processSounds() {
  m_viewManager.processSounds(m_rSoundManager);
}

string const& SampleGame::getGameName() { return m_gameName; }
