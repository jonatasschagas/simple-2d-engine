#pragma once
#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

#include "graphics/GraphicsManager.hpp"
#include "input/InputManager.hpp"
#include "sound/SoundManager.hpp"
#include "view/Game.hpp"

class Game;
class GLFWwindow;

GLFWwindow* initializeOpenGLRenderer(int argc, char** argv, int screenWidth,
                                     int screenHeight, string const& gameName,
                                     float& dpiX, float& dpiY);
int mainLoopOpenGLRenderer(GLFWwindow* pWindow, Game& rGame,
                           InputManager& rInputManager);

#endif /* OPENGLRENDERER_H */