//
//  Head.hpp
//  simple-2d-engine-opengl
//
//  Created by Jonatas Chagas on 28.8.2023.
//
#pragma once
#ifndef Head_hpp
#define Head_hpp

#include <stdio.h>
#include "core/Sprite.hpp"
#include <string>
#include "view/Maze.hpp"

class Head : public Sprite {
public:
    
  Head(const string& headSpritePath, const float speed, const Maze* const pMaze);
  ~Head();
  
  enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
  };
  
  void update(float deltaTime) override;
  
  void setDirection(Direction direction);
  
private:
  
  float m_speed;
  float m_speedAccumulator;
  Direction m_direction;
  const Maze* const m_pMaze;

  void initializeMembers() {
    m_speed = 0;
    m_speedAccumulator = 0;
    m_direction = Direction::RIGHT;
  }
  
};

#endif /* Head_hpp */
