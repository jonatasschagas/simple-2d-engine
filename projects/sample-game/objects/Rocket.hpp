#pragma once

#ifndef Rocket_hpp
#define Rocket_hpp

#include "core/Sprite.hpp"
#include <string>
#include <vector>

class Rocket : public Sprite {
 public:
  Rocket(float speed);
  ~Rocket() {}

  void update(float delta) override;

 private:
  float m_speed = 0.05f;
  float m_accumulatedDelta = 0.0f;
  int m_angle = 0;
};

#endif /* Rocket_hpp */