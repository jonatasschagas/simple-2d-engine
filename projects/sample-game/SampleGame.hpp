#pragma once

#ifndef SampleGame_hpp
#define SampleGame_hpp

#include "view/Game.hpp"
#include "view/ViewManager.hpp"
#include <string>

using std::string;

class SampleGame : public Game {
 public:
  SampleGame(GraphicsManager& rGraphicsManager, SoundManager& rSoundManager,
             InputManager& rInputManager);
  ~SampleGame();

  void initialize() override;

  string const& getGameName() override;

 private:
   string m_gameName;

  void initializeMembers() { m_gameName = "Sample Game"; }
};

#endif /* SampleGame_hpp */