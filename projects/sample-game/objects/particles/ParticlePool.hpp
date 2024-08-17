#pragma once

#ifndef ParticlePool_hpp
#define ParticlePool_hpp

#include "Particle.hpp"
#include "core/StructuralSprite.hpp"
#include <string>
#include <vector>

class ParticlePool : public StructuralSprite {
 public:
  ParticlePool(int numParticles, glm::vec4 color);
  ~ParticlePool() {}

  void update(float delta) override;

  void create(float x, float y, float speed, float angle, int lifetime);

  int getNumParticles() const { return m_particles.size(); }

 private:
  std::vector<Particle> m_particles;
  Particle* m_pFirstAvailable;
  glm::vec4 m_color;
};

#endif /* ParticlePool_hpp */