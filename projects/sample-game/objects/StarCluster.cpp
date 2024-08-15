#include "StarCluster.hpp"

StarCluster::StarCluster(unsigned numStars, unsigned numPlanets) : Sprite() {
  initializeCluster(numStars, m_starsCluster);
  initializePlanets(numPlanets, m_planets);
}

void StarCluster::initializeCluster(unsigned numStars,
                                    std::vector<Sprite>& starsCluster) {
  for (unsigned i = 0; i < numStars; i++) {
    Sprite star;
    star.setColor(255, 255, 255, 255);
    float size = (rand() % 30) / 100.0f;
    star.setSize(size, size);
    star.setXY(rand() % 100, rand() % 100);
    starsCluster.push_back(star);
  }

  for (Sprite& star : starsCluster) {
    addChild(&star);
  }
}

void StarCluster::initializePlanets(unsigned numPlanets,
                                    std::vector<RotatingPlanet>& planets) {
  for (unsigned i = 0; i < numPlanets; i++) {
    float const y = rand() % 100;
    float const x = rand() % 100;
    float const size = rand() % 20;
    float const speed = rand() % 5 / 100.0f;

    planets.emplace_back(speed,
                         "assets/images/planet0" + std::to_string(i) + ".png",
                         x, y, size, size, true);
  }

  for (RotatingPlanet& rotatingPlanet : planets) {
    rotatingPlanet.setPivotAtCenter();
    addChild(&rotatingPlanet);
  }
}

void StarCluster::update(float delta) { Sprite::update(delta); }