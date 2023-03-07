#pragma once
#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

#include "platform/GraphicsManager.hpp"
#include "platform/SoundManager.hpp"
#include "view/Game.hpp"

class Game;
class GLFWwindow;

struct OpenGLRenderer {
  int screenWidth;
  int screenHeight;
  float previousTimeSeconds;
  Game* pGame;
};

GLFWwindow* initializeOpenGLRenderer(int argc, char** argv, int screenWidth,
                                     int screenHeight, string const& gameName);
int mainLoopOpenGLRenderer(GLFWwindow* pWindow, Game& rGame, int screenWidth,
                           int screenHeight, GraphicsManager& rGraphicsManager,
                           SoundManager& rSoundManager);

#endif /* OPENGLRENDERER_H */