#include "Sprite.hpp"
#include <glm/gtx/transform.hpp>

class SpriteCmp {
 public:
  bool operator()(Sprite const* p1, Sprite const* p2) const {
    return p1->getY() > p2->getY();
  }
};

Sprite::Sprite()
{
  initializeMembers();
  setRotation(0);
}

Sprite::~Sprite() { initializeMembers(); }

void Sprite::showPivot() {
  m_pPivotSprite = new Sprite();
  m_pPivotSprite->loadTexture("assets/pivot.png");
  m_pPivotSprite->useFullTexture();
  m_pPivotSprite->setSize(.1f, .1f);
  m_pPivotSprite->setXY(4.5f, 4.5f);
  addChild(m_pPivotSprite);
}

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
  // translation * rotation * scale (also known as TRS matrix)

  glm::vec3 coords = m_coords;
  glm::vec3 size = m_size;
  
  if (m_pParent != nullptr) {
    coords = m_coords / (m_pParent->m_coords + m_pParent->m_size);
    size  =  m_size / m_pParent->m_size;
  }
  
  if (m_angle > 0) {
    
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
    glm::mat4 rotationMatrix = transformY * transformX * transformZ;
    
    return glm::translate(glm::mat4(1.0f), coords) * rotationMatrix * glm::scale(glm::mat4(1.0f), size) * glm::translate(glm::mat4(1.0f), -coords);
  } else {
    return glm::translate(glm::mat4(1.0f), coords) * glm::scale(glm::mat4(1.0f), size);
  }
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
  m_coords = glm::vec3(x, y, 0);
}

void Sprite::setSize(float w, float h) {
  m_size = glm::vec3(w, h, 0);
}

void Sprite::setTextureCoordinates(float x, float y, float w, float h) {
  m_textureCoordinates = glm::vec4(x, y, w, h);
}

void Sprite::setRotation(float degrees) {
  m_angle = degrees;
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

void Sprite::fillParent() {
  if (m_pParent == nullptr) return;

  setSize(1.0f, 1.0f);
}
