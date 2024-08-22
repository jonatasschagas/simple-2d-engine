#pragma once

#ifndef Rocket_hpp
#define Rocket_hpp

#include "core/TexturedSprite.hpp"
#include "particles/ParticlePool.hpp"
#include <string>
#include <vector>

class Rocket : public TexturedSprite {
 public:
  Rocket(float speed);
  ~Rocket() {}

  void update(float delta) override;

  void moveUp();
  void moveDown();
  void moveLeft();
  void moveRight();

 private:
  void emitParticles();

  float m_speed = 0.05f;
  float m_accumulatedDelta = 0.0f;
  float m_particlesAccumulatedDelta = 0.0f;
  float m_originalY = 0.0f;
  int m_angle = 0;

  ParticlePool m_particlePool;
};

#endif /* Rocket_hpp */