#pragma once

#ifndef StarCluster_hpp
#define StarCluster_hpp

#include "RotatingPlanet.hpp"
#include "Star.hpp"
#include "core/StructuralSprite.hpp"
#include <string>
#include <vector>

class StarCluster : public StructuralSprite {
 public:
  StarCluster(unsigned numStars, unsigned numPlanets);
  ~StarCluster() {}

  void update(float delta) override;

 private:
  void initializeCluster(unsigned numStars);
  void initializePlanets(unsigned numPlanets);

  std::vector<Star> m_starsCluster = {};
  std::vector<RotatingPlanet> m_planets = {};
};

#endif /* StarCluster_hpp */