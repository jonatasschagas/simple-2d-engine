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

void Sprite::processSounds(SoundManager& rSoundManager) {
  while (!m_soundsToPlay.empty()) {
    string sound = m_soundsToPlay.front();
    m_soundsToPlay.pop();
    rSoundManager.playSoundEffect(sound);
  }
}

void Sprite::render(GraphicsManager& rGraphicsManager) {
  if (!m_visible) return;

  if (hasTexture() && !m_textureLoaded) {
    // lazy loading...
    Texture texture = rGraphicsManager.loadTexture(m_textureFilename);
    m_textureLoaded = true;
    if (m_useWholeTexture) {
      m_textureWidth = texture.width;
      m_textureHeight = texture.height;
      setTextureCoordinates(0, 0, m_textureWidth, m_textureHeight);
    }
  }

  if (hasTexture()) {
    rGraphicsManager.renderTexture(m_worldTransform, m_textureCoordinates,
                                   m_textureFilename);
  } else if (m_colorSpecified) {
    rGraphicsManager.renderColoredSprite(m_worldTransform, m_color);
  }

  for (Sprite* pChild : m_children) {
    pChild->render(rGraphicsManager);
  }
}

void Sprite::clearChildrenToRemove() {
  // cleaning up
  if (m_childrenToRemove.size() > 0) {
    for (Sprite const* pChildToRemove : m_childrenToRemove) {
      auto i = m_children.begin();
      while (i != m_children.end()) {
        if ((*i) == pChildToRemove) {
          i = m_children.erase(i);
        }
        ++i;
      }
    }
    m_childrenToRemove.clear();
  }
}

void Sprite::update(float deltaTime) {
  if (!m_visible) return;

  clearChildrenToRemove();

  if (m_pParent != nullptr) {
    // Compute parent's world transform
    glm::mat4 parentTransform = m_pParent->m_worldTransform;

    // Compute child's local transform
    glm::mat4 localTransform = calculateChildTransform();

    // Combine with parent's world transform
    m_worldTransform = parentTransform * localTransform;
  } else {
    m_worldTransform = calculateParentTransform();
  }

  for (Sprite* pChild : m_children) {
    pChild->update(deltaTime);
  }
}

glm::mat4 Sprite::calculateParentTransform() {
  glm::mat4 translate =
      glm::translate(glm::mat4(1.0f), glm::vec3(m_coords.x, m_coords.y, 0.0f));

  glm::mat4 scale =
      glm::scale(glm::mat4(1.0f), glm::vec3(m_size.x, m_size.y, 1.0f));

  glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(m_angle),
                                   glm::vec3(0.0f, 0.0f, 1.0f));

  glm::mat4 model = translate * rotation * scale;

  return model;
}

glm::mat4 Sprite::calculateChildTransform() {
  // THIS WORKS NOW

  // Translate to the child's position
  glm::mat4 translate =
      glm::translate(glm::mat4(1.0f), glm::vec3(m_coords.x, m_coords.y, 0.0f));

  // Apply scaling to the child
  glm::mat4 scale =
      glm::scale(glm::mat4(1.0f), glm::vec3(m_size.x, m_size.y, 1.0f));

  // Calculate the pivot in world space, considering the object's size
  glm::vec3 pivot = glm::vec3(m_pivot.x * m_size.x, m_pivot.y * m_size.y, 0.0f);
  glm::mat4 pivotTranslate = glm::translate(glm::mat4(1.0f), pivot);
  glm::mat4 inversePivotTranslate = glm::translate(glm::mat4(1.0f), -pivot);

  // Apply rotation around the pivot
  glm::mat4 rotation = glm::rotate(glm::mat4(1.0f), glm::radians(m_angle),
                                   glm::vec3(0.0f, 0.0f, 1.0f));

  glm::mat4 model =
      translate * pivotTranslate * rotation * scale * inversePivotTranslate;

  return model;
}

void Sprite::playSoundEffect(string const& soundName) {
  m_soundsToPlay.push(soundName);
}

void Sprite::addChild(Sprite* pChild) {
  m_children.push_back(pChild);
  pChild->m_pParent = this;

  if (!m_sortChildren) return;

  m_children.sort(SpriteCmp());
}

void Sprite::setXY(float x, float y) {
  m_coords.x = x;
  m_coords.y = y;
}

void Sprite::setSize(float w, float h) {
  m_size.x = w;
  m_size.y = h;
}

void Sprite::removeChild(Sprite* pChildToRemove) {
  m_childrenToRemove.push_back(pChildToRemove);
}

void Sprite::removeAllChildren() { m_children.clear(); }

void Sprite::setAlpha(float const alpha) {
  m_alpha = alpha;
  for (Sprite* pChild : m_children) {
    pChild->setAlpha(alpha);
  }
}

void Sprite::fillParent() {
  if (m_pParent == nullptr) return;

  setSize(1.0f, 1.0f);
}
