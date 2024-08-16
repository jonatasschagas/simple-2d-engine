#include "Rocket.hpp"
#include "utils/MathUtils.h"

Rocket::Rocket(float speed)
    : Sprite(),
      m_speed(speed),
      m_particlePool(500, glm::vec4(255, 69, 0, 255)) {
  loadTexture("assets/images/rocket.png");
  setWholeTexture(true);
  setRotation(90);

  addChild(&m_particlePool);

  m_particlePool.setXY(0, 0);
  m_particlePool.setSize(100.f, 100.f);
}
void Rocket::update(float delta) {
  Sprite::update(delta);

  if (m_originalY == 0.0f) {
    m_originalY = getY();
  }

  m_accumulatedDelta += delta;
  if (m_accumulatedDelta > m_speed) {
    float sinCal = sinf(degreesToRadians(m_angle));
    setXY(getX(), sinCal * 5.f + m_originalY);

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

  if (m_particlesAccumulatedDelta == 0 || m_particlesAccumulatedDelta > 0.05f) {
    emitParticles();
    m_particlesAccumulatedDelta = 0.0f;
  }
  m_particlesAccumulatedDelta += delta;
}

void Rocket::emitParticles() {
  for (int i = 0; i < (10 + rand() % 300); i++) {
    float x = 30;
    float y = 100;
    float speed = -1.f;
    float angle = 200 + rand() % 150;
    int lifetime = rand() % 100;
    m_particlePool.create(x, y, speed, angle, lifetime);
  }
}