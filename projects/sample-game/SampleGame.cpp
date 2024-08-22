#include "SampleGame.hpp"
#include "view/GameView.hpp"
#include <glm/glm.hpp>

SampleGame::SampleGame(GraphicsManager& rGraphicsManager,
                       SoundManager& rSoundManager, InputManager& rInputManager)
    : Game(rGraphicsManager, rSoundManager, rInputManager) {
  initializeMembers();
}

SampleGame::~SampleGame() { initializeMembers(); }

void SampleGame::initialize() {
  GameView* pGameView = new GameView();
  addView("game-view", pGameView);

  switchView("game-view");
}

string const& SampleGame::getGameName() { return m_gameName; }
