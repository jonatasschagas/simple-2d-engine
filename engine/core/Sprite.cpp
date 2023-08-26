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
  setRotation(0);
}

Sprite::~Sprite() { initializeMembers(); }

void Sprite::loadTexture(string const& textureFileName) {
  m_textureFilename = textureFileName;
}

void Sprite::useFullTexture() {
  m_useWholeTexture = true;
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
    rGraphicsManager.renderTexture(m_worldTransform, m_textureCoordinates, m_textureFilename);
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

  m_transform = calculateTransform();
  
  if (m_pParent != nullptr) {
    m_worldTransform = m_pParent->m_worldTransform * m_transform;
  } else {
    m_worldTransform = m_transform;
  }

  for (Sprite* pChild : m_children) {
    pChild->update(deltaTime);
  }
}

glm::mat4 Sprite::calculateTransform() {
  // translation * rotation * scale (also know as TRS matrix)

  const glm::mat4 transformX = glm::rotate(glm::mat4(1.0f),
                                           glm::radians(0.0f),
                                           glm::vec3(1.0f, 0.0f, 0.0f));
  const glm::mat4 transformY = glm::rotate(glm::mat4(1.0f),
                                           glm::radians(0.0f),
                                           glm::vec3(0.0f, 1.0f, 0.0f));
  const glm::mat4 transformZ = glm::rotate(glm::mat4(1.0f),
                                           glm::radians(m_angle),
                                           glm::vec3(0.0f, 0.0f, 1.0f));
    // Y * X * Z
  glm::mat4 rotation = transformY * transformX * transformZ;
  
  glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(m_size.x, m_size.y, .0f));
  glm::mat4 translate = glm::translate(glm::mat4(1.0f), glm::vec3(m_coords.x, m_coords.y, .0f));
  
  glm::vec3 pivot = m_pivot * m_size;
  glm::mat4 model = translate * rotation * scale * glm::translate(glm::mat4(1.0f), -pivot);
  
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

void Sprite::setX(float x) { m_coords = glm::vec3(x, m_coords.y, 0); }

void Sprite::setY(float y) { m_coords = glm::vec3(m_coords.x, y, 9); }

void Sprite::setXY(float x, float y) { m_coords = glm::vec3(x, y, 0); }

void Sprite::setSize(float w, float h) {
  m_size.x = w;
  m_size.y = h;
}

void Sprite::setTextureCoordinates(float x, float y, float w, float h) {
  m_textureCoordinates = glm::vec4(x, y, w, h);
}

void Sprite::setRotation(float degrees) {
  m_angle = degrees;
}

void Sprite::setPivotAtCenter() {
  m_pivot.x = 0.5f;
  m_pivot.y = 0.5f;
}

void Sprite::setPivot(float x, float y) {
  m_pivot.x = x;
  m_pivot.y = y;
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

Vector2 Sprite::getGamePosition() const {
  return Vector2(m_coords.x, m_coords.y);
}

float Sprite::getX() const { return m_coords.x; }

float Sprite::getY() const { return m_coords.y; }

float Sprite::getWidth() const { return m_size.x; };

float Sprite::getHeight() const { return m_size.y; };

bool Sprite::hasTexture() const { return m_textureFilename.size() > 0; };

bool const Sprite::isFlipped() const { return m_flip; }

void Sprite::setFlip(bool const flip) { m_flip = flip; }

Sprite* Sprite::getParent() const { return m_pParent; }

void Sprite::setTileMap(bool tileMap) { m_tileMap = tileMap; }

void Sprite::fillParent() {
  if (m_pParent == nullptr) return;

  setSize(1.0f, 1.0f);
}
