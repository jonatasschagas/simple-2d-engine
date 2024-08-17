#include "Particle.hpp"
#include "utils/MathUtils.h"

Particle::Particle() : ColoredSprite() {
  setColor(0, 0, 0, 0);
  setSize(5.f, 5.f);
}

void Particle::update(float delta) {
  if (!isActive()) {
    return;
  }

  ColoredSprite::update(delta);

  float dx = cubicEaseOut(m_framesLeft, 0,
                          m_speed * cos(degreesToRadians(m_angle)), m_lifetime);
  float dy = cubicEaseOut(m_framesLeft, 0,
                          m_speed * sin(degreesToRadians(m_angle)), m_lifetime);

  setXY(getX() + dx, getY() + dy);
  setColor(m_color.r, m_color.g, m_color.b,
           m_color.a * (m_framesLeft / (float)m_lifetime));
  m_framesLeft--;
  if (m_framesLeft <= 0) {
    setVisible(false);
  }
}

void Particle::activate(float x, float y, float speed, float angle,
                        int lifetime, glm::vec4 color) {
  setXY(x, y);
  setVisible(true);
  setColor(color.r, color.g, color.b, color.a);
  m_speed = speed;
  m_angle = angle;
  m_framesLeft = lifetime;
  m_lifetime = lifetime;
  m_color = color;
}