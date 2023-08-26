//
//  Earth.cpp
//  simple-2d-engine-opengl
//
//  Created by Jonatas Chagas on 23.8.2023.
//

#include "Earth.hpp"

Earth::Earth() : Sprite() {
  initializeMembers();
  loadTexture("assets/images/awesomeface.png");
  useFullTexture();
  setXY(5, 5);
  setPivot(50, 50);
  setSize(0.1f, 0.1f); // relative to its parent
}

void Earth::update(float deltaTime) {
  
  m_rotationAccumulator += deltaTime;
  
  //if (m_rotationAccumulator > 0.05f) {
    //m_rotationAccumulator = 0;
    m_rotation += deltaTime * 100;
    setRotation(m_rotation);
    if (m_rotation > 360) {
      m_rotation = 0;
    }
  //}
  
  
  Sprite::update(deltaTime);
}
