#pragma once

#ifndef RotatingPlanet_hpp
#define RotatingPlanet_hpp

#include "core/Sprite.hpp"
#include <string>

class RotatingPlanet : public Sprite {
 public:
  RotatingPlanet(float rotatingSpeed, std::string const& textureFileName,
                 float x, float y, float w, float h, bool pivotCenter);
  ~RotatingPlanet();

  void update(float delta) override;

 private:
  double m_rotationAccumulator = 0;
  unsigned m_rotation = 0;
  float m_rotatingSpeed = 0;
};

#endif /* RotatingPlanet_hpp */