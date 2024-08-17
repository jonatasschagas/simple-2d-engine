#include "StarCluster.hpp"
#include "core/ColoredSprite.hpp"

StarCluster::StarCluster(unsigned numStars, unsigned numPlanets)
    : StructuralSprite() {
  initializeCluster(numStars);
  initializePlanets(numPlanets);
}

void StarCluster::initializeCluster(unsigned numStars) {
  for (unsigned i = 0; i < numStars; i++) {
    ColoredSprite star;
    star.setColor(255, 255, 255, 255);
    float size = (rand() % 30) / 100.0f;
    star.setSize(size, size);
    star.setXY(rand() % 100, rand() % 100);
    m_starsCluster.push_back(star);
  }

  for (Sprite& star : m_starsCluster) {
    addChild(&star);
  }
}

void StarCluster::initializePlanets(unsigned numPlanets) {
  for (unsigned i = 0; i < numPlanets; i++) {
    float const y = rand() % 100;
    float const x = rand() % 100;
    float const size = rand() % 20;
    float const speed = rand() % 5 / 100.0f;

    m_planets.emplace_back(speed,
                           "assets/images/planet0" + std::to_string(i) + ".png",
                           x, y, size, size, true);
  }

  for (RotatingPlanet& rotatingPlanet : m_planets) {
    rotatingPlanet.setPivotAtCenter();
    addChild(&rotatingPlanet);
  }
}

void StarCluster::update(float delta) { StructuralSprite::update(delta); }