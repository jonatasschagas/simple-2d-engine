#ifndef Game_hpp
#define Game_hpp

#include "event/EventListener.hpp"
#include "platform/GraphicsManager.hpp"
#include "platform/SoundManager.hpp"
#include <string>

using namespace std;

class Game : public EventListener {
 public:
  virtual void initialize(Vector2 const& screenSizeInGameUnits) = 0;
  virtual void receiveEvent(Event* pEvent) = 0;
  virtual void update(float const deltaTime) = 0;
  virtual void updateEditor(float const deltaTime) = 0;
  virtual void render(GraphicsManager& rGraphicsManager) = 0;
  virtual void processSounds(SoundManager& rSoundManager) = 0;
  virtual string const& getGameName() = 0;
};

#endif /* Game_hpp */
