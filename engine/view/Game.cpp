#include "Game.hpp"

Game::Game(GraphicsManager& rGraphicsManager, SoundManager& rSoundManager,
           InputManager& rInputManager)
    : m_rGraphicsManager(rGraphicsManager),
      m_rSoundManager(rSoundManager),
      m_rInputManager(rInputManager),
      m_viewManager(rGraphicsManager.getScreenSizeInGameUnits(),
                    rInputManager) {}

void Game::update(float const deltaTime) { m_viewManager.update(deltaTime); }

void Game::render() { m_viewManager.render(m_rGraphicsManager); }

void Game::processSounds() { m_viewManager.processSounds(m_rSoundManager); }

void Game::addView(string const& viewName, View* pView) {
  m_viewManager.addView(viewName, pView);
}

void Game::switchView(string const& viewName) {
  m_viewManager.switchView(viewName);
}
