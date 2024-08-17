#include "RotatingPlanet.hpp"

RotatingPlanet::RotatingPlanet(float rotatingSpeed,
                               std::string const& textureFileName, float x,
                               float y, float w, float h, bool pivotCenter)
    : m_rotatingSpeed(rotatingSpeed) {
  setXY(x, y);
  setSize(w, h);
  loadTexture(textureFileName);
  setWholeTexture(true);
  if (pivotCenter) {
    setPivotAtCenter();
  }
}

RotatingPlanet::~RotatingPlanet() {}

void RotatingPlanet::update(float delta) {
  Sprite::update(delta);

  m_rotationAccumulator += delta;

  if (m_rotationAccumulator > m_rotatingSpeed) {
    m_rotationAccumulator = 0;
    m_rotation++;
    setRotation(m_rotation);
    if (m_rotation > 360) {
      m_rotation = 0;
    }
  }
}