#include "SampleGame.hpp"
#include "view/GameView.hpp"
#include <glm/glm.hpp>

SampleGame::SampleGame() : m_viewManager(Vector2::ZERO) { initializeMembers(); }

SampleGame::~SampleGame() { initializeMembers(); }

void SampleGame::initialize(Vector2 const& screenSizeInGameUnits) {
  m_viewManager = ViewManager(screenSizeInGameUnits);

  GameView* pGameView = new GameView();
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

void SampleGame::render(GraphicsManager& rGraphicsManager) {
  m_viewManager.render(rGraphicsManager);
}

void SampleGame::processSounds(SoundManager& rSoundManager) {
  m_viewManager.processSounds(rSoundManager);
}

string const& SampleGame::getGameName() { return m_gameName; }
