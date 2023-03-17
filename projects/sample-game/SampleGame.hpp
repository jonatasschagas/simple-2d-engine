#pragma once

#ifndef SampleGame_hpp
#define SampleGame_hpp

#include "view/Game.hpp"
#include "view/ViewManager.hpp"
#include <string>

using namespace std;

class SampleGame : public Game {
 public:
  SampleGame();
  ~SampleGame();

  void initialize(Vector2 const& screenSizeInGameUnits) override;
  void receiveEvent(Event* pEvent) override;
  void update(float const deltaTime) override;
  void updateEditor(float const deltaTime) override;
  void render(GraphicsManager& rGraphicsManager) override;
  void processSounds(SoundManager& rSoundManager) override;
  string const& getGameName() override;

 private:
  ViewManager m_viewManager;
  string m_gameName;

  void initializeMembers() { m_gameName = "Sample Game"; }
};

#endif /* SampleGame_hpp */