#include "StarField.hpp"

StarField::StarField(unsigned numStars, float speed)
    : Sprite(), m_cluster1(200, 3), m_cluster2(200, 2), m_speed(speed) {
  setSize(1.f, 1.f);
  setXY(0, 0);

  addChild(&m_cluster1);
  addChild(&m_cluster2);

  m_cluster1.setXY(0, 0);
  m_cluster1.setSize(1.0f, 1.0f);

  m_cluster2.setXY(1.0f, 0);
  m_cluster2.setSize(1.0f, 1.0f);
}

void StarField::update(float delta) {
  Sprite::update(delta);

  m_accumulatedDelta += delta;

  if (m_accumulatedDelta > m_speed) {
    m_cluster1.setX(m_cluster1.getX() - 0.001f);
    m_cluster2.setX(m_cluster2.getX() - 0.001f);

    if (m_cluster1.getX() < -1.0f) {
      m_cluster1.setX(1.0f);
    }

    if (m_cluster2.getX() < -1.0f) {
      m_cluster2.setX(1.0f);
    }

    m_accumulatedDelta = 0;
  }
}