//
//  Head.cpp
//  simple-2d-engine-opengl
//
//  Created by Jonatas Chagas on 28.8.2023.
//

#include "Head.hpp"

#define SPEED_INCREMENT 0.1f

Head::Head(const string& headSpritePath, const float speed, const Maze* const pMaze) : Sprite(), m_pMaze(pMaze) {
  initializeMembers();
  
  loadTexture(headSpritePath);
  useFullTexture();
  m_speed = speed;
}

Head::~Head(){}

void Head::setDirection(Direction direction) {
  m_direction = direction;
}

void Head::update(float deltaTime) {
  m_speedAccumulator += deltaTime;
  
  if (m_speedAccumulator > m_speed) {
    m_speedAccumulator = 0;
    
    float nextX = getX();
    float nextY = getY();

    switch(m_direction) {
      case Direction::UP:
        nextY = getY() - SPEED_INCREMENT;
        if (!m_pMaze->canMoveUp(nextY)) {
          m_direction = Direction::LEFT;
        } else {
          setXY(nextX, nextY);
        }
        break;
      case Direction::DOWN:
        nextY = getY() + SPEED_INCREMENT;
        if (!m_pMaze->canMoveDown(nextY)) {
          m_direction = Direction::RIGHT;
        } else {
          setXY(nextX, nextY);
        }
        break;
      case Direction::RIGHT:
        nextX = getX() + SPEED_INCREMENT;
        if (!m_pMaze->canMoveRight(nextX)) {
          m_direction = Direction::UP;
        } else {
          setXY(nextX, nextY);
        }
        break;
      case Direction::LEFT:
        nextX = getX() - SPEED_INCREMENT;
        if (!m_pMaze->canMoveLeft(nextX)) {
          m_direction = Direction::DOWN;
        } else {
          setXY(nextX, nextY);
        }
        break;
    };
    
  }
  
  Sprite::update(deltaTime);
}

