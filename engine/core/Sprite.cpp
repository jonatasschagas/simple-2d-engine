#include "Sprite.hpp"
#include <glm/gtx/transform.hpp>

class SpriteCmp {
 public:
  bool operator()(Sprite const* p1, Sprite const* p2) const {
    return p1->getY() > p2->getY();
  }
};

Sprite::Sprite() {
  initializeMembers();

  m_scale = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
  m_rotation = glm::rotate(0.0f, glm::vec3(1.0f));
}

Sprite::~Sprite() { initializeMembers(); }

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

  if (!isVisibleInParent(rGraphicsManager)) {
    return;
  }

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

  for (Sprite* pChild : m_children) {
    pChild->render(rGraphicsManager);
  }
}

void Sprite::update(float deltaTime) {
  if (!m_visible) return;

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

  float w = m_size.x;
  float h = m_size.y;

  if (m_pParent != nullptr) {
    m_transform = calculateTransform();
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
    m_transform = calculateTransform();

    m_points[0] = m_transform * glm::vec4(0.0f, 0.0f, 1.0, 1.0);
    m_points[1] = m_transform * glm::vec4(w, h, 1.0, 1.0);
    m_worldTransform = m_transform;
  }

  for (Sprite* pChild : m_children) {
    pChild->update(deltaTime);
  }
}

glm::mat4 Sprite::calculateTransform() {
  glm::vec2 pivot;

  if (m_pivotCentered) {
    pivot = glm::vec2(m_coords.x + m_size.x / 2, m_coords.y + m_size.y / 2);
  } else {
    pivot = glm::vec2(m_coords.x, m_coords.y);
  }

  glm::mat4 moveToOrigin =
      glm::translate(glm::mat4(1.0f), glm::vec3(-pivot.x, -pivot.y, 1.0f));
  glm::mat4 moveBackToPivot =
      glm::translate(glm::mat4(1.0f), glm::vec3(pivot.x, pivot.y, 1.0f));

  glm::mat4 transformationMatrix;
  float x = m_centeredOnParentX ? 0 : m_coords.x;
  float y = m_centeredOnParentY ? 0 : m_coords.y;

  m_transform = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, 1.0f));
  transformationMatrix =
      moveBackToPivot * m_rotation * m_scale * moveToOrigin * m_transform;

  return transformationMatrix;
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

void Sprite::removeChild(Sprite* pChildToRemove) {
  m_childrenToRemove.push_back(pChildToRemove);
}

bool Sprite::isVisibleInParent(GraphicsManager const& rGraphicsManager) const {
  return true;
}

void Sprite::removeAllChildren() { m_children.clear(); }

void Sprite::setAlpha(float const alpha) {
  m_alpha = alpha;
  for (Sprite* pChild : m_children) {
    pChild->setAlpha(alpha);
  }
}

void Sprite::setVertices(vector<Vertex> const& vertices) {
  m_drawCall.vertices = vertices;
}

Vector2 Sprite::getScreenPosition() const {
  return Vector2(getTransformedX(), getTransformedY());
}

Vector2 Sprite::getGamePosition() const {
  return Vector2(m_coords.x, m_coords.y);
}

float Sprite::getX() const { return m_coords.x; }

float Sprite::getY() const { return m_coords.y; }

float Sprite::getWidth() const { return m_size.x; };

float Sprite::getHeight() const { return m_size.y; };

float Sprite::getTransformedX() const { return m_points[0].x; }

float Sprite::getTransformedY() const { return m_points[0].y; }

bool Sprite::hasTexture() const { return m_textureFilename.size() > 0; };

bool const Sprite::isFlipped() const { return m_flip; }

void Sprite::setFlip(bool const flip) { m_flip = flip; }

Sprite* Sprite::getParent() const { return m_pParent; }

void Sprite::setTileMap(bool tileMap) { m_tileMap = tileMap; }

void Sprite::fillParent() {
  if (m_pParent == nullptr) return;

  float parentWidth = m_pParent->getWidth();
  float parentHeight = m_pParent->getHeight();

  setSize(parentWidth, parentHeight);
}