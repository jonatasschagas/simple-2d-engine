#include "StarCluster.hpp"
#include "core/ColoredSprite.hpp"

StarCluster::StarCluster(unsigned numStars, unsigned numPlanets)
    : StructuralSprite() {
  initializeCluster(numStars);
  initializePlanets(numPlanets);
}

void StarCluster::initializeCluster(unsigned numStars) {
  for (unsigned i = 0; i < numStars; i++) {
    glm::vec4 randomColor =
        glm::vec4(rand() % 255, rand() % 255, rand() % 255, 255);
    Star star(randomColor);
    float size = (rand() % 100) / 50.0f;
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
    float const x = rand() % 100;
    float const y = rand() % 100;
    float const width = rand() % 20;
    float const height = width;
    float const speed = 1.0f / width;

    m_planets.emplace_back(speed,
                           "assets/images/planet0" + std::to_string(i) + ".png",
                           x, y, width, height, true);
  }

  for (RotatingPlanet& rotatingPlanet : m_planets) {
    rotatingPlanet.setPivotAtCenter();
    addChild(&rotatingPlanet);
  }
}

void StarCluster::update(float delta) { StructuralSprite::update(delta); }