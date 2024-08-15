#pragma once
#ifndef Sprite_hpp
#define Sprite_hpp

#include "core/Vector2.h"
#include "glm/glm.hpp"
#include "platform/GraphicsManager.hpp"
#include "platform/SoundManager.hpp"
#include <list>
#include <queue>
#include <stdio.h>
#include <string>

using namespace std::string_literals;

class Sprite {
 public:
  Sprite() = default;
  Sprite(float x, float y, float w, float h);

  void playSoundEffect(string const& soundName);

  /**
   * @brief The engine expects the x,y of sprites that have a parent to be in
   * the range of 0-100, where 100 is 100% of the parent's size. This function
   * takes care of converting the x,y to the correct coordinates.
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
   * For sprites that don't have a parent, the width and height are in the range
   * of 0-MAX_GAME_UNITS, where MAX_GAME_UNITS is define when wiring the game.
   */
  void setSize(float w, float h);

  void fillParent();

  void setAlpha(float const alpha);

  virtual void update(float deltaTime);
  virtual void render(GraphicsManager& rGraphicsManager);
  virtual void processSounds(SoundManager& rSoundManager);

  void addChild(Sprite* pChild);
  list<Sprite*> const& getChildren() const;
  void removeChild(Sprite* pChild);
  void removeAllChildren();

  void setSortChildren(bool sortChildren);

  Vector2 getGamePosition() const { return Vector2(m_coords.x, m_coords.y); }

  float getX() const { return m_coords.x; }

  float getY() const { return m_coords.y; }

  float getWidth() const { return m_size.x; };

  float getHeight() const { return m_size.y; };

  bool hasTexture() const { return m_textureFilename.size() > 0; };

  bool const isFlipped() const { return m_flip; }

  void setFlip(bool const flip) { m_flip = flip; }

  Sprite* getParent() const { return m_pParent; }

  void setTextureCoordinates(float x, float y, float w, float h) {
    m_textureCoordinates = glm::vec4(x, y, w, h);
  }

  void setRotation(float degrees) { m_angle = degrees; }
  float getRotation() const { return m_angle; }

  void setPivotAtCenter() {
    m_pivot.x = .5f;
    m_pivot.y = .5f;
  }

  void setPivot(float x, float y) {
    m_pivot.x = x;
    m_pivot.y = y;
  }

  void setX(float x) { setXY(x, m_coords.y); }

  void setY(float y) { setXY(m_coords.x, y); }

  void setColor(float r, float g, float b, float a) {
    m_color = glm::vec4(r, g, b, a);
    m_colorSpecified = true;
  }

  void loadTexture(string const& textureFileName) {
    m_textureFilename = textureFileName;
  }

  void setWholeTexture(bool useWholeTexture) {
    m_useWholeTexture = useWholeTexture;
  }

 protected:
  Sprite* m_pParent = nullptr;
  float m_alpha = 1.0f;

  glm::vec3 m_coords = {0, 0, 0};
  glm::vec3 m_size = {0, 0, 0};
  glm::vec3 m_pivot = {0, 0, 0};  // between 0 and 1
  glm::vec3 m_scaleFactor = {1, 1, 1};

  glm::vec4 m_color = {0, 0, 0, 0};
  bool m_colorSpecified = false;

  glm::mat4 calculateTransform();
  void clearChildrenToRemove();

  string m_textureFilename = "";
  bool m_textureLoaded = false;
  int m_textureWidth = 0;
  int m_textureHeight = 0;
  bool m_useWholeTexture = false;

  bool m_visible = true;
  float m_angle = 0;

  glm::vec4 m_textureCoordinates = {0, 0, 0, 0};
  bool m_flip = false;

  std::queue<string> m_soundsToPlay;

  glm::mat4 m_worldTransform = glm::mat4(1.0f);

  std::list<Sprite*> m_children;
  std::list<Sprite*> m_childrenToRemove;

  bool m_sortChildren = false;
};

#endif /* Sprite_hpp */