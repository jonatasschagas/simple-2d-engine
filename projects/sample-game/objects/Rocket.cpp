#include "Rocket.hpp"
#include "utils/MathUtils.h"

Rocket::Rocket(float speed)
    : TexturedSprite(),
      m_speed(speed),
      m_particlePool(1000, glm::vec4(255, 69, 0, 255)) {
  loadTexture("assets/images/rocket.png");
  setWholeTexture(true);
  setRotation(90);

  addChild(&m_particlePool);

  m_particlePool.setXY(20, -19);
  m_particlePool.setSize(100.f, 100.f);
}

void Rocket::update(float delta) {
  TexturedSprite::update(delta);

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
  for (int i = 0; i < (10 + rand() % 500); i++) {
    float x = 30;
    float y = 100;
    float speed = -1.5f + (rand() % 10) / 10.0f;
    float angle = 200 + rand() % 150;
    int lifetime = rand() % 300;
    m_particlePool.create(x, y, speed, angle, lifetime);
  }
}

void Rocket::moveLeft() { setXY(getX() - m_speed * 10, getY()); }

void Rocket::moveRight() { setXY(getX() + m_speed * 10, getY()); }