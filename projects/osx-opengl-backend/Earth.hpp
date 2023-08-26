//
//  Earth.hpp
//  simple-2d-engine-opengl
//
//  Created by Jonatas Chagas on 23.8.2023.
//

#ifndef Earth_hpp
#define Earth_hpp

#include <stdio.h>
#include "core/Sprite.hpp"


class Earth : public Sprite
{
public:
  
  Earth();
  
  void update(float deltaTime) override;
private:
  
  int m_rotation;
  float m_rotationAccumulator;
  
  void initializeMembers() {
    m_rotation = 0;
    m_rotationAccumulator = 0;
  }
  
};

#endif /* Earth_hpp */
