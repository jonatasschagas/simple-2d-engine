#include "Sprite.hpp"
#include <glm/gtx/transform.hpp>
#include <iostream>

class SpriteCmp {
 public:
  bool operator()(Sprite const* p1, Sprite const* p2) const {
    return p1->getY() > p2->getY();
  }
};

Sprite::Sprite(float x, float y, float w, float h) {
  setXY(x, y);
  setSize(w, h);
}

Sprite::~Sprite() {
  for (Sprite* pChild : m_children) {
    if (pChild->m_onRemoveFromParent) {
      pChild->m_onRemoveFromParent(
          pChild);  // TODO: fix this by using smart pointers
    }
  }
}

void Sprite::processSounds(SoundManager& rSoundManager) {
  while (!m_soundsToPlay.empty()) {
    string sound = m_soundsToPlay.front();
    m_soundsToPlay.pop();
    rSoundManager.playSoundEffect(sound);
  }
}

void Sprite::render(GraphicsManager& rGraphicsManager) {
  if (!m_visible) return;

  if (m_dirty) {
    m_localTransform = calculateTransform(rGraphicsManager);
    m_dirty = false;
  }

  // update world transform
  if (m_pParent != nullptr) {
    m_worldTransform =
            m_pParent->m_worldTransform * m_localTransform;
  } else {
    m_worldTransform = m_localTransform;
  }

  renderSprite(rGraphicsManager);

  // render children
  for (Sprite* pChild : m_children) {
    pChild->render(rGraphicsManager);
  }
}

void Sprite::clearChildrenToRemove() {
  // cleaning up
  if (m_childrenToRemove.size() > 0) {
    for (Sprite* pChildToRemove : m_childrenToRemove) {
      auto i = m_children.begin();
      while (i != m_children.end()) {
        if ((*i) == pChildToRemove) {
          i = m_children.erase(i);
          if (pChildToRemove->m_onRemoveFromParent) {
            pChildToRemove->m_onRemoveFromParent(
                pChildToRemove);  // TODO: fix this by using smart pointers
          }
        }
        ++i;
      }
    }
    m_childrenToRemove.clear();
  }
}

void Sprite::update(float deltaTime) {
  clearChildrenToRemove();

  if (!m_visible) return;

  for (Sprite* pChild : m_children) {
    pChild->update(deltaTime);
  }
}

glm::mat4 Sprite::calculateTransform(GraphicsManager& rGraphicsManager) const {
  // translation * rotation * scale (also known as TRS matrix)

  glm::vec3 size = m_computedSize;

  if (m_pParent == nullptr) {
    float scaleFactorX, scaleFactorY;
    rGraphicsManager.getScaleFactor(scaleFactorX, scaleFactorY);
    size = m_computedSize * glm::vec3(scaleFactorX, scaleFactorY, 1.0f);
  }

  return glm::translate(glm::mat4(1.0f), m_computedCoords) *
         glm::translate(glm::mat4(1.0f), m_pivot * size) *
         glm::rotate(glm::mat4(1.0f), glm::radians(m_angle),
                     glm::vec3(0.0f, 0.0f, 1.0f)) *
         glm::translate(glm::mat4(1.0f), -m_pivot * size) *
         glm::scale(glm::mat4(1.0f), size);
}

void Sprite::playSoundEffect(string const& soundName) {
  m_soundsToPlay.push(soundName);
}

void Sprite::addChild(Sprite* pChild) {
  m_children.push_back(pChild);
  pChild->m_pParent = this;

  // set child's coordinates and size relative to parent
  pChild->setXY(pChild->getX(), pChild->getY());
  pChild->setSize(pChild->getWidth(), pChild->getHeight());

  if (!m_sortChildren) return;

  m_children.sort(SpriteCmp());
}

void Sprite::setXY(float x, float y) {
  m_coords.x = x;
  m_coords.y = y;

  if (m_pParent != nullptr) {
    m_computedCoords.x = x / 100.f;
    m_computedCoords.y = y / 100.f;
  } else {
    m_computedCoords.x = x;
    m_computedCoords.y = y;
  }

  m_dirty = true;
}

void Sprite::setSize(float w, float h) {
  m_size.x = w;
  m_size.y = h;

  if (m_pParent != nullptr) {
    m_computedSize.x = w / 100.0f;
    m_computedSize.y = h / 100.0f;
  } else {
    m_computedSize.x = w;
    m_computedSize.y = h;
  }

  m_dirty = true;
}

void Sprite::removeChild(Sprite* pChildToRemove) {
  m_childrenToRemove.push_back(pChildToRemove);
}

void Sprite::removeAllChildren() { m_children.clear(); }

void Sprite::fillParent() {
  if (m_pParent == nullptr) return;

  setSize(100.f, 100.f);
}

glm::vec2 Sprite::getTrueSizeInPixels(
    GraphicsManager const& graphicsManager) const {
  glm::vec2 size = m_size;

  if (m_pParent == nullptr) {
    float scaleFactorX, scaleFactorY;
    graphicsManager.getScaleFactor(scaleFactorX, scaleFactorY);
    size.x = m_size.x * scaleFactorX;
    size.y = m_size.y * scaleFactorY;
  } else {
    size.x =
        m_size.x * m_pParent->getTrueSizeInPixels(graphicsManager).x / 100.f;
    size.y =
        m_size.y * m_pParent->getTrueSizeInPixels(graphicsManager).y / 100.f;
  }

  return size;
}

glm::vec2 Sprite::getTruePositionInPixels(
    GraphicsManager const& graphicsManager) const {
  glm::vec2 pos = m_coords;

  if (m_pParent == nullptr) {
    float scaleFactorX, scaleFactorY;
    graphicsManager.getScaleFactor(scaleFactorX, scaleFactorY);
    pos.x = m_coords.x * scaleFactorX;
    pos.y = m_coords.y * scaleFactorY;
  } else {
    glm::vec2 parentPos = m_pParent->getTruePositionInPixels(graphicsManager);
    pos.x =
        parentPos.x +
        m_coords.x * m_pParent->getTrueSizeInPixels(graphicsManager).x / 100.f;
    pos.y =
        parentPos.y +
        m_coords.y * m_pParent->getTrueSizeInPixels(graphicsManager).y / 100.f;
  }
  return pos;
}