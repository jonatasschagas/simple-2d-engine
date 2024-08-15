#include "StarCluster.hpp"

StarCluster::StarCluster(unsigned numStars, unsigned numPlanets) : Sprite() {
  setSize(1.0f, 1.0f);
  setXY(0, 0);

  initializeCluster(numStars, m_starsCluster);
  initializePlanets(numPlanets, m_planets);
}

void StarCluster::initializeCluster(unsigned numStars,
                                    std::vector<Sprite>& starsCluster) {
  for (unsigned i = 0; i < numStars; i++) {
    Sprite star;
    star.setColor(255, 255, 255, 255);
    star.setSize(.005f, .005f);
    star.setXY((rand() % 100) / 100.0f, (rand() % 100) / 100.0f);
    starsCluster.push_back(star);
  }

  for (Sprite& star : starsCluster) {
    addChild(&star);
  }
}

void StarCluster::initializePlanets(unsigned numPlanets,
                                    std::vector<RotatingPlanet>& planets) {
  for (unsigned i = 0; i < numPlanets; i++) {
    float const x = (rand() % 100) / 100.0f;
    float const y = (rand() % 100) / 100.0f;
    float const size = (rand() % 20) / 100.0f;
    float const speed = rand() % 10 / 100.0f;

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