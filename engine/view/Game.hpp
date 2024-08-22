#ifndef Game_hpp
#define Game_hpp

#include "event/EventListener.hpp"
#include "graphics/GraphicsManager.hpp"
#include "input/InputManager.hpp"
#include "sound/SoundManager.hpp"
#include "view/ViewManager.hpp"
#include <string>

using std::string;

class Game {
 public:
  Game(GraphicsManager& rGraphicsManager, SoundManager& rSoundManager,
       InputManager& rInputManager);
  virtual ~Game() {}

  /** Initialize the game, switch initial view */
  virtual void initialize() = 0;

  /** Update the game state
   * @param deltaTime the time since the last update in seconds
   */
  void update(float const deltaTime);

  /** Render the game */
  void render();

  /** Process sounds */
  void processSounds();

  /** return the name of the game
   * @return the name of the game
   */
  virtual string const& getGameName() = 0;

 protected:
  /** Used by derived classes to add views to the game
   * @param viewName the name of the view
   * @param pView the view to add
   */
  void addView(string const& viewName, View* pView);

  /** Used by derived classes to switch views
   * @param viewName the name of the view to switch to
   */
  void switchView(string const& viewName);

 private:
  GraphicsManager& m_rGraphicsManager;
  SoundManager& m_rSoundManager;
  InputManager& m_rInputManager;
  ViewManager m_viewManager;

  bool m_initialized = false;
};

#endif /* Game_hpp */
