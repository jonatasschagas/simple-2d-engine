//
//  Maze.hpp
//  simple-2d-engine-opengl
//
//  Created by Jonatas Chagas on 1.9.2023.
//
#pragma once
#ifndef Maze_h
#define Maze_h

class Maze
{
public:
  
  virtual bool canMoveRight(float x) const = 0;
  virtual bool canMoveLeft(float x) const = 0;
  virtual bool canMoveUp(float y) const = 0;
  virtual bool canMoveDown(float y) const = 0;
  
};

#endif /* Maze_h */
