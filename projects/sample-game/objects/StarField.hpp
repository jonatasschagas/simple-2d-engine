#pragma once

#ifndef StarField_hpp
#define StarField_hpp

#include "StarCluster.hpp"
#include "core/ColoredSprite.hpp"
#include <string>
#include <vector>

class StarField : public ColoredSprite {
 public:
  StarField(unsigned numStars, float speed);
  ~StarField() {}

  void update(float delta) override;

 private:
  float m_speed = 0.05f;
  float m_accumulatedDelta = 0.0f;

  StarCluster m_cluster1;
  StarCluster m_cluster2;
};

#endif /* StarField_hpp */