#pragma once

#ifndef Particle_hpp
#define Particle_hpp

#include "core/ColoredSprite.hpp"
#include <string>
#include <vector>

class Particle : public ColoredSprite {
  friend class ParticlePool;

 public:
  Particle();
  ~Particle() {}

  void update(float delta) override;

  void activate(float x, float y, float speed, float angle, int lifetime,
                glm::vec4 color);
  bool isActive() const { return m_framesLeft > 0; }

 private:
  Particle* m_pNext;
  int m_framesLeft = 0;
  int m_lifetime = 0;
  float m_speed = 0.0f;
  float m_angle = 0.0f;
};

#endif /* Particle_hpp */