#include "Rocket.hpp"
#include "utils/MathUtils.h"

Rocket::Rocket(float speed) : m_speed(speed) {
  loadTexture("assets/images/rocket.png");
  setWholeTexture(true);
  setRotation(90);
}

void Rocket::update(float delta) {
  Sprite::update(delta);

  if (m_originalY == 0.0f) {
    m_originalY = getY();
  }

  m_accumulatedDelta += delta;
  if (m_accumulatedDelta > m_speed) {
    float sinCal = sinf(degreesToRadians(m_angle));
    setXY(getX(), sinCal * 0.1f + m_originalY);

    if (sinCal > 0) {
      setRotation(simple_lerp(getRotation(), 80, delta));
    } else {
      setRotation(simple_lerp(getRotation(), 100, delta));
    }

    m_angle += 1;
    if (m_angle > 360) {
      m_angle = 0;
    }

    m_accumulatedDelta = 0.0f;
  }
}