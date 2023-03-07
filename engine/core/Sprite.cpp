#include "Sprite.hpp"
#include <glm/gtx/transform.hpp>

Sprite::Sprite() {
  initializeMembers();

  m_scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
  m_rotation = glm::rotate(0.0f, glm::vec3(1.0f));
}

Sprite::~Sprite() {
  // removeAllChildren();

  // delete m_pDrawCall;

  initializeMembers();
}

void Sprite::loadTexture(string const& textureFileName) {
  m_textureFilename = textureFileName;
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

  bool const notVisibleInParent =
      m_pParent != nullptr && !m_pParent->isVisibleInParent(this);
  if (notVisibleInParent) return;

  if (hasTexture() && !m_textureLoaded) {
    rGraphicsManager.loadTexture(m_textureFilename);
    m_textureLoaded = true;
  }

  if (hasTexture() || m_drawCall.vertices.size() > 0) {
    m_drawCall.spriteProperties.x = m_points[0].x;
    m_drawCall.spriteProperties.y = m_points[0].y;
    m_drawCall.spriteProperties.w = m_points[1].x - m_points[0].x;
    m_drawCall.spriteProperties.h = m_points[1].y - m_points[0].y;

    m_drawCall.settings.tileMap = m_tileMap;
    m_drawCall.settings.flipHorizontal = m_flip;

    m_drawCall.textureSettings.name = m_textureFilename;
    m_drawCall.textureSettings.x = (int)m_textureCoordinates.x;
    m_drawCall.textureSettings.y = (int)m_textureCoordinates.y;
    m_drawCall.textureSettings.w = (int)m_textureCoordinates.z;
    m_drawCall.textureSettings.h = (int)m_textureCoordinates.w;
    m_drawCall.textureSettings.alpha = m_alpha;

    rGraphicsManager.renderTexture(m_drawCall);
  }

  for (int i = 0; i < m_children.size(); i++) {
    Sprite* pChild = m_children[i];
    pChild->render(rGraphicsManager);
  }
}

void Sprite::update(float deltaTime) {
  if (!m_visible) return;

  if (m_childrenToRemove.size() > 0) {
    for (int i = 0; i < m_childrenToRemove.size(); i++) {
      Sprite* pChildToRemove = m_childrenToRemove[i];
      removeChildForced(pChildToRemove);
    }
    m_childrenToRemove.clear();
  }

  float w = m_size.x;
  float h = m_size.y;

  if (m_pParent != nullptr) {
    if (!m_pParent->isVisibleInParent(this)) return;

    m_transform = calculateTransform(this);
    m_worldTransform = m_pParent->m_worldTransform * m_transform;

    m_points[0] = m_worldTransform * glm::vec4(0.0f, 0.0f, 1.0, 1.0);
    m_points[1] = m_worldTransform * glm::vec4(w, h, 1.0, 1.0);

    if (m_centeredOnParentX || m_centeredOnParentY) {
      float offsetX = 0;
      float offsetY = 0;

      if (m_centeredOnParentX) {
        float parentWidth = m_pParent->getWidth();
        float width = getWidth();
        offsetX = (parentWidth - width) / 2;
      }

      if (m_centeredOnParentY) {
        float parentHeight = m_pParent->getHeight();
        float height = getHeight();
        offsetY = (parentHeight - height) / 2;
      }

      glm::mat4 offsetMat =
          glm::translate(glm::mat4(1.0f), glm::vec3(offsetX, offsetY, 1.0f));
      m_worldTransform = offsetMat * m_worldTransform;

      m_points[0] = m_worldTransform * glm::vec4(0.0f, 0.0f, 1.0, 1.0);
      m_points[1] = m_worldTransform * glm::vec4(w, h, 1.0, 1.0);
    }
  } else {
    m_transform = calculateTransform(this);

    m_points[0] = m_transform * glm::vec4(0.0f, 0.0f, 1.0, 1.0);
    m_points[1] = m_transform * glm::vec4(w, h, 1.0, 1.0);
    m_worldTransform = m_transform;
  }

  for (int i = 0; i < m_children.size(); i++) {
    Sprite* pChild = m_children[i];
    pChild->update(deltaTime);
  }
}

glm::mat4 Sprite::calculateTransform(Sprite* pSprite) {
  glm::vec2 pivot;

  if (m_pivotCentered)
    pivot = glm::vec2(pSprite->m_coords.x + pSprite->m_size.x / 2,
                      pSprite->m_coords.y + pSprite->m_size.y / 2);
  else
    pivot = glm::vec2(pSprite->m_coords.x, pSprite->m_coords.y);

  glm::mat4 moveToOrigin =
      glm::translate(glm::mat4(1.0f), glm::vec3(-pivot.x, -pivot.y, 1.0f));
  glm::mat4 moveBackToPivot =
      glm::translate(glm::mat4(1.0f), glm::vec3(pivot.x, pivot.y, 1.0f));

  glm::mat4 transformationMatrix;
  float x = m_centeredOnParentX ? 0 : m_coords.x;
  float y = m_centeredOnParentY ? 0 : m_coords.y;

  pSprite->m_transform = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 1.0f));
  transformationMatrix = moveBackToPivot * pSprite->m_rotation *
                         pSprite->m_scale * moveToOrigin * pSprite->m_transform;

  return transformationMatrix;
}

void Sprite::playSoundEffect(string const& soundName) {
  m_soundsToPlay.push(soundName);
}

void Sprite::addChild(Sprite* pChild) {
  m_children.push_back(pChild);
  pChild->m_pParent = this;

  if (!m_sortChildren) return;

  // sort sprites by Y coordinate
  // sprites with lower Y are in front of the sprites with higher Y
  struct less_than_y {
    inline bool operator()(Sprite* pS1, Sprite* pS2) {
      return pS1->getY() > pS2->getY();
    }
  };
  sort(m_children.begin(), m_children.end(), less_than_y());
}

void Sprite::setX(float x) { m_coords = glm::vec2(x, m_coords.y); }

void Sprite::setY(float y) { m_coords = glm::vec2(m_coords.x, y); }

void Sprite::setXY(float x, float y) { m_coords = glm::vec2(x, y); }

void Sprite::setSize(float w, float h) { m_size = glm::vec2(w, h); }

void Sprite::setTextureCoordinates(float x, float y, float w, float h) {
  m_textureCoordinates = glm::vec4(x, y, w, h);
}

void Sprite::setScale(float scaleLevel) {
  m_scale =
      glm::scale(glm::mat4(1.0f), glm::vec3(scaleLevel, scaleLevel, 1.0f));
}

void Sprite::setRotation(float degrees) {
  m_rotation = glm::rotate(glm::mat4(1.0f), degrees, glm::vec3(1.0f));
}

void Sprite::setPivotAtCenter(bool pivotAtCenter) {
  m_pivotCentered = pivotAtCenter;
}

void Sprite::removeChild(int const index) {
  m_children.erase(m_children.begin() + index);
}

void Sprite::removeChild(Sprite* pChildToRemove) {
  m_childrenToRemove.push_back(pChildToRemove);
}

void Sprite::removeChildForced(Sprite* pChildToRemove) {
  int indexToRemove = -1;
  for (int i = 0; i < m_children.size(); i++) {
    Sprite* pChild = m_children[i];
    if (pChild == pChildToRemove) {
      indexToRemove = i;
      delete pChild;
      break;
    }
  }
  if (indexToRemove > -1) removeChild(indexToRemove);
}

bool Sprite::isVisibleInParent(Sprite* pChild) const {
  if (m_pParent != nullptr) return m_pParent->isVisibleInParent(pChild);

  return true;
}

void Sprite::removeAllChildren() {
  for (int i = 0; i < m_children.size(); i++) {
    Sprite* pChild = m_children[i];
    delete pChild;
  }
  m_children.clear();
}

void Sprite::setAlpha(float const alpha) {
  m_alpha = alpha;
  for (int i = 0; i < m_children.size(); i++) {
    Sprite* pChild = m_children[i];
    pChild->setAlpha(alpha);
  }
}

void Sprite::setVertices(vector<Vertex>& vertices) {
  m_drawCall.vertices = vertices;
}

void Sprite::destroy() {
  if (m_pParent != nullptr) {
    m_pParent->removeChild(this);
  } else {
    removeAllChildren();
    delete this;
  }
}

Vector2 Sprite::getScreenPosition() {
  return Vector2(getTransformedX(), getTransformedY());
}

Vector2 Sprite::getGamePosition() { return Vector2(m_coords.x, m_coords.y); }

float Sprite::getX() const { return m_coords.x; }

float Sprite::getY() const { return m_coords.y; }

float Sprite::getWidth() const { return m_size.x; };

float Sprite::getHeight() const { return m_size.y; };

float Sprite::getTransformedX() const { return m_points[0].x; }

float Sprite::getTransformedY() const { return m_points[0].y; }

bool Sprite::hasTexture() const { return m_textureFilename.size() > 0; };

bool const Sprite::isFlipped() const { return m_flip; }

void Sprite::setFlip(bool const flip) { m_flip = flip; }
