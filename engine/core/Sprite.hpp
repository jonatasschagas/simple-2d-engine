#pragma once
#ifndef Sprite_hpp
#define Sprite_hpp

#include "glm/glm.hpp"
#include "graphics/GraphicsManager.hpp"
#include "sound/SoundManager.hpp"
#include <functional>
#include <list>
#include <queue>
#include <stdio.h>
#include <string>

using std::list;
using std::string;

/**
 * @brief The Sprite class is the base class for all sprites in the game. It
 * provides functionality for rendering, updating, and playing sound effects.
 * @ingroup graphics
 */
class Sprite {
 public:
  Sprite() = default;
  Sprite(float x, float y, float w, float h);

  virtual ~Sprite();

  /**
   * @brief Plays a sound effect
   * @param soundName the name of the sound effect to play
   */
  void playSoundEffect(string const& soundName);

  /**
   * @brief The engine expects the x,y of sprites that have a parent to be in
   * the range of 0-100, where 100 is 100% of the parent's size. This function
   * takes care of converting the x,y to the correct coordinates.
   *
   * For example, if the parent is 100x100 and the x,y are 50,50, the sprite
   * will be in the center of the parent. If the parent is 100x100 and the x,y
   * are 100,100, the sprite will be in the bottom right corner of the parent.
   *
   * For sprites that don't have a parent, the x,y are in the range of 0-1000,
   * where 1000 is the size of the screen.
   *
   * @param x
   * @param y
   */
  void setXY(float x, float y);

  /**
   * @brief The engine expects the width and height of sprites that have a
   * parent to be in the range of 0-100, where 100 is 100% of the parent's size.
   * This function takes care of converting the width and height to the correct
   * size.
   *
   * For example, if the parent is 100x100 and the width and height are 50,50,
   * the sprite will be half the size of the parent. If the parent is 100x100
   * and the width and height are 100,100, the sprite will be the same size as
   * the parent.
   *
   * For sprites that don't have a parent, the width and height are in the range
   * of 0-MAX_GAME_UNITS, where MAX_GAME_UNITS is define when wiring the game.
   */
  void setSize(float w, float h);

  /**
   * @brief Fills the parent with the sprite
   * */
  void fillParent();

  /**
   * @brief Updates the sprite
   * @param deltaTime the time since the last update
   */
  virtual void update(float deltaTime);

  /**
   * @brief Renders the sprite
   * @param rGraphicsManager the graphics manager
   */
  virtual void render(GraphicsManager& rGraphicsManager);

  /**
   * @brief Processes the sounds for the sprite
   * @param rSoundManager the sound manager
   */
  virtual void processSounds(SoundManager& rSoundManager);

  /**
   * @brief Adds a child to the sprite
   * @param pChild the child to add
   */
  void addChild(Sprite* pChild);

  /**
   * @brief Returns the children of the sprite
   * @return the children of the sprite
   */
  list<Sprite*> const& getChildren() const;

  /**
   * @brief Removes a child from the sprite
   * @param pChild the child to remove
   */
  void removeChild(Sprite* pChild);

  /**
   * @brief Removes all children from the sprite
   */
  void removeAllChildren();

  /**
   * @brief Sets the sort children flag
   * @param sortChildren the flag to set
   */
  void setSortChildren(bool sortChildren);

  /**
   * @brief returns the x coordinate of the sprite
   * @return the x coordinate of the sprite
   */
  float getX() const { return m_coords.x; }

  /**
   * @brief returns the y coordinate of the sprite
   * @return the y coordinate of the sprite
   */
  float getY() const { return m_coords.y; }

  /**
   * @brief returns the width of the sprite
   * @return the width of the sprite
   */
  float getWidth() const { return m_size.x; };

  /**
   * @brief returns the height of the sprite
   * @return the height of the sprite
   */
  float getHeight() const { return m_size.y; };

  /**
   * @brief returns the parent of the sprite
   * @return the parent of the sprite
   */
  Sprite* getParent() const { return m_pParent; }

  /**
   * @brief sets the rotation of the sprite
   * @param degrees the rotation in degrees
   */
  void setRotation(float degrees) { m_angle = degrees; }

  /**
   * @brief returns the rotation of the sprite
   * @return the rotation of the sprite
   */
  float getRotation() const { return m_angle; }

  /**
   * @brief sets the pivot of the sprite to be centered
   */
  void setPivotAtCenter() {
    m_pivot.x = .5f;
    m_pivot.y = .5f;
  }

  /**
   * @brief sets the pivot of the sprite
   * @param x the x coordinate of the pivot
   * @param y the y coordinate of the pivot
   */
  void setPivot(float x, float y) {
    m_pivot.x = x;
    m_pivot.y = y;
  }

  /**
   * @brief sets the x coordinate of the sprite
   * @param x the x coordinate of the sprite
   */
  void setX(float x) { setXY(x, m_coords.y); }

  /**
   * @brief sets the y coordinate of the sprite
   * @param y the y coordinate of the sprite
   */
  void setY(float y) { setXY(m_coords.x, y); }

  /**
   * @brief sets the visible flag of the sprite
   * @param visible the flag to set
   */
  void setVisible(bool visible) { m_visible = visible; }

  /**
   * @brief returns the visible flag of the sprite
   * @return the visible flag of the sprite
   */
  bool isVisible() const { return m_visible; }

  /**
   * @brief returns the size of the sprite in pixels
   * @param graphicsManager the graphics manager
   * @return the world transform of the sprite
   */
  glm::vec2 getTrueSizeInPixels(GraphicsManager const& graphicsManager) const;

  /**
   * @brief returns the world transform of the sprite
   * @param graphicsManager the graphics manager
   * @return the world transform of the sprite
   */
  glm::vec2 getTruePositionInPixels(
      GraphicsManager const& graphicsManager) const;

  /**
   * @brief callback for when the sprite is removed from its parent
   * @param onRemoveFromParent the callback to set
   */
  void setOnRemoveFromParent(std::function<void(Sprite*)> onRemoveFromParent) {
    m_onRemoveFromParent = onRemoveFromParent;
  }

 protected:
  /**
   * @brief renders the sprite and should be implemented by the derived class
   * @param rGraphicsManager the graphics manager
   */
  virtual void renderSprite(GraphicsManager& rGraphicsManager) = 0;

  // methods
  glm::mat4 calculateTransform(GraphicsManager& rGraphicsManager) const;
  void clearChildrenToRemove();

  // members
  glm::vec3 m_coords = {0, 0, 0};
  glm::vec3 m_computedCoords = {0, 0, 0};
  glm::vec3 m_size = {0, 0, 0};
  glm::vec3 m_computedSize = {0, 0, 0};
  glm::vec3 m_pivot = {0, 0, 0};  // between 0 and 1

  bool m_visible = true;
  float m_angle = 0;

  std::queue<string> m_soundsToPlay;

  glm::mat4 m_worldTransform = glm::mat4(1.0f);

  Shader* m_pShader = nullptr;

  Sprite* m_pParent = nullptr;
  std::list<Sprite*> m_children;
  std::list<Sprite*> m_childrenToRemove;
  bool m_sortChildren = false;

  std::function<void(Sprite*)> m_onRemoveFromParent = nullptr;
};

#endif /* Sprite_hpp */