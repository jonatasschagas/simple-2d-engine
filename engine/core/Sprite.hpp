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

  void showPivot();
  
  void setXY(float x, float y);
  void setSize(float w, float h);
  void setTextureCoordinates(float x, float y, float w, float h);
  void setRotation(float degrees);
  
  void useFullTexture();
    
  float getX() const;
  float getY() const;
  float getWidth() const;
  float getHeight() const;
  Vector2 getGamePosition() const;

  void fillParent();

  bool const isFlipped() const;

  void setAlpha(float const alpha);
  void setFlip(bool const flip);
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
  float m_alpha;

 private:
  
  glm::mat4 calculateTransform();

  glm::vec3 m_coords;
  glm::vec3 m_size;

  string m_textureFilename;
  bool m_textureLoaded;
  int m_textureWidth;
  int m_textureHeight;
  bool m_useWholeTexture;
  
  bool m_visible;
  float m_angle;

  glm::vec4 m_textureCoordinates;
  bool m_flip;

  queue<string> m_soundsToPlay;

  DrawCall m_drawCall;

  glm::mat4 m_worldTransform;
  glm::mat4 m_transform;
  
  list<Sprite*> m_children;
  list<Sprite*> m_childrenToRemove;
  
  Sprite* m_pPivotSprite;

  bool m_sortChildren;

  void initializeMembers() {
    m_pParent = nullptr;
    m_textureFilename = "";
    m_textureLoaded = false;
    m_textureWidth = 0;
    m_textureHeight = 0;
    m_useWholeTexture = false;
    m_alpha = 1.f;
    m_angle = 0;
    m_flip = false;
    m_children.clear();
    m_visible = true;
    m_pPivotSprite = nullptr;
    
    m_coords.x = 0;
    m_coords.y = 0;
    m_coords.z = 0;
    m_size.x = 0;
    m_size.y = 0;
    m_size.z = 0;
    
    m_textureCoordinates.x = 0;
    m_textureCoordinates.y = 0;
    m_textureCoordinates.z = 0;
    m_textureCoordinates.w = 0;

    m_soundsToPlay.empty();
  }
};

#endif /* Sprite_hpp */
