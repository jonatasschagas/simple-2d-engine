#include "SampleGame.hpp"
#include "view/GameView.hpp"
#include <glm/glm.hpp>

SampleGame::SampleGame() { initializeMembers(); }

SampleGame::~SampleGame() { initializeMembers(); }

void SampleGame::initialize() {
  m_viewManager = ViewManager();

  GameView* pGameView = new GameView();
  m_viewManager.addView("game-view", pGameView);
  m_viewManager.switchView("game-view");
}

void SampleGame::receiveEvent(Event* pEvent) {}

void SampleGame::update(float const deltaTime) {
  m_viewManager.update(deltaTime);
}

void SampleGame::updateEditor(float const deltaTime) {}

void SampleGame::render(GraphicsManager& rGraphicsManager) {
  m_viewManager.render(rGraphicsManager);
}

void SampleGame::processSounds(SoundManager& rSoundManager) {
  m_viewManager.processSounds(rSoundManager);
}

string const& SampleGame::getGameName() { return m_gameName; }
