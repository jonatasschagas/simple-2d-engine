#include "StarField.hpp"

StarField::StarField(unsigned numStars, float speed)
    : ColoredSprite(), m_cluster1(200, 1), m_cluster2(200, 2), m_speed(speed) {
  setColor(0, 0, 0, 255);
  addChild(&m_cluster1);
  addChild(&m_cluster2);

  m_cluster1.setXY(0, 0);
  m_cluster1.setSize(100.f, 100.f);

  m_cluster2.setXY(100.0f, 0);
  m_cluster2.setSize(100.f, 100.f);
}

void StarField::update(float delta) {
  ColoredSprite::update(delta);

  m_accumulatedDelta += delta;

  if (m_accumulatedDelta > m_speed) {
    m_cluster1.setX(m_cluster1.getX() - 0.1f);
    m_cluster2.setX(m_cluster2.getX() - 0.1f);

    if (m_cluster1.getX() < -100.f) {
      m_cluster1.setX(100.f);
    }

    if (m_cluster2.getX() < -100.f) {
      m_cluster2.setX(100.f);
    }

    m_accumulatedDelta = 0;
  }
}