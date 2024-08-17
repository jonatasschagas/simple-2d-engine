#ifndef Game_hpp
#define Game_hpp

#include "event/EventListener.hpp"
#include "graphics/GraphicsManager.hpp"
#include "sound/SoundManager.hpp"
#include <string>

using std::string;

class Game : public EventListener {
 public:
  Game(GraphicsManager& rGraphicsManager, SoundManager& rSoundManager)
      : m_rGraphicsManager(rGraphicsManager), m_rSoundManager(rSoundManager) {}

  virtual void initialize() = 0;
  virtual void receiveEvent(Event* pEvent) = 0;
  virtual void update(float const deltaTime) = 0;
  virtual void updateEditor(float const deltaTime) = 0;
  virtual void render() = 0;
  virtual void processSounds() = 0;
  virtual string const& getGameName() = 0;

 protected:
  GraphicsManager& m_rGraphicsManager;
  SoundManager& m_rSoundManager;
};

#endif /* Game_hpp */
