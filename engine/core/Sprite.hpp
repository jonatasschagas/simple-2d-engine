#pragma once
#ifndef Sprite_hpp
#define Sprite_hpp

#include "Vector2.h"
#include "glm/glm.hpp"
#include "platform/DrawCall.h"
#include "platform/GraphicsManager.hpp"
#include "platform/SoundManager.hpp"
#include <list>
#include <queue>
#include <stdio.h>
#include <string>

using namespace std;

class Sprite : enable_shared_from_this<Sprite> {
 public:
  Sprite();
  virtual ~Sprite();

  void loadTexture(string const& textureFileName);

  void playSoundEffect(string const& soundName);

  void setX(float x);
  void setY(float y);
  void setXY(float x, float y);
  void setSize(float w, float h);
  void setTextureCoordinates(float x, float y, float w, float h);
  void setScale(float scaleLevel);
  void setRotation(float degrees);
  void setTextureRotation(float degrees);
  void setPivotAtCenter(bool pivotAtCenter);
  void setCenteredOnParentX(bool centeredOnParentX);
  void setCenteredOnParentY(bool centeredOnParentY);

  float getX() const;
  float getY() const;
  float getWidth() const;
  float getHeight() const;
  float getTransformedX() const;
  float getTransformedY() const;
  Vector2 getScreenPosition() const;
  Vector2 getGamePosition() const;

  void fillParent();

  bool const isFlipped() const;

  void setAlpha(float const alpha);
  void setFlip(bool const flip);
  void setTileMap(bool const tileMap);
  void setVisible(bool visible);
  bool isVisible() const;

  virtual void update(float deltaTime);
  virtual void render(GraphicsManager& rGraphicsManager);
  virtual void processSounds(SoundManager& rSoundManager);

  void addChild(Sprite* pChild);
  list<Sprite*> const& getChildren() const;
  void removeChild(Sprite* pChild);
  void removeAllChildren();

  Sprite* getParent() const;

  virtual bool isVisibleInParent(GraphicsManager const& rGraphicsManager) const;

  bool hasTexture() const;

  void setSortChildren(bool sortChildren);

  void setVertices(vector<Vertex> const& vertices);

 protected:
  Sprite* m_pParent;
  glm::vec2 m_size;
  float m_alpha;

 private:
  glm::vec2 m_coords;

  glm::mat4 calculateTransform();

  string m_textureFilename;
  bool m_textureLoaded;

  bool m_centeredOnParentX;
  bool m_centeredOnParentY;
  bool m_pivotCentered;
  bool m_visible;
  float m_angle;

  glm::vec4 m_points[2];
  glm::vec4 m_textureCoordinates;
  bool m_flip;
  bool m_tileMap;

  queue<string> m_soundsToPlay;

  DrawCall m_drawCall;

  glm::mat4 m_worldTransform;
  glm::mat4 m_transform;
  glm::mat4 m_rotation;
  glm::mat4 m_scale;

  list<Sprite*> m_children;
  list<Sprite*> m_childrenToRemove;

  bool m_sortChildren;

  void initializeMembers() {
    m_pParent = nullptr;
    m_textureFilename = "";
    m_textureLoaded = false;
    m_alpha = 1.f;
    m_angle = 0;
    m_flip = false;
    m_children.clear();
    m_pivotCentered = false;
    m_centeredOnParentX = false;
    m_centeredOnParentY = false;
    m_visible = true;
    m_tileMap = false;

    m_coords.x = 0;
    m_coords.y = 0;
    m_size.x = 0;
    m_size.y = 0;

    m_textureCoordinates.x = 0;
    m_textureCoordinates.y = 0;
    m_textureCoordinates.z = 0;
    m_textureCoordinates.w = 0;

    m_soundsToPlay.empty();
  }
};

#endif /* Sprite_hpp */
