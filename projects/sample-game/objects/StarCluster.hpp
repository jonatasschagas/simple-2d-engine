#pragma once

#ifndef StarCluster_hpp
#define StarCluster_hpp

#include "RotatingPlanet.hpp"
#include "core/Sprite.hpp"
#include <string>
#include <vector>

class StarCluster : public Sprite {
 public:
  StarCluster(unsigned numStars, unsigned numPlanets);
  ~StarCluster() {}

  void update(float delta) override;

 private:
  void initializeCluster(unsigned numStars, std::vector<Sprite>& starsCluster);
  void initializePlanets(unsigned numPlanets,
                         std::vector<RotatingPlanet>& planets);

  std::vector<Sprite> m_starsCluster = {};
  std::vector<RotatingPlanet> m_planets = {};
};

#endif /* StarCluster_hpp */