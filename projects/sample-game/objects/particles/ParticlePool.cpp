#include "ParticlePool.hpp"

ParticlePool::ParticlePool(int numParticles, glm::vec4 color)
    : StructuralSprite(), m_particles(numParticles), m_color(color) {
  for (int i = 0; i < numParticles; i++) {
    addChild(&m_particles[i]);
  }

  m_pFirstAvailable = &m_particles[0];

  for (int i = 0; i < numParticles - 1; i++) {
    m_particles[i].m_pNext = &m_particles[i + 1];
  }

  m_particles[numParticles - 1].m_pNext = nullptr;
}

void ParticlePool::update(float delta) {
  Sprite::update(delta);
  for (int i = 0; i < m_particles.size(); i++) {
    if (!m_particles[i].isActive()) {
      m_particles[i].m_pNext = m_pFirstAvailable;
      m_pFirstAvailable = &m_particles[i];
    }
  }
}

void ParticlePool::create(float x, float y, float speed, float angle,
                          int lifetime) {
  assert(m_pFirstAvailable != nullptr);

  Particle* pNewParticle = m_pFirstAvailable;
  m_pFirstAvailable = pNewParticle->m_pNext;

  pNewParticle->activate(x, y, speed, angle, lifetime, m_color);
}