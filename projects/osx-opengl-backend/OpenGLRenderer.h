#pragma once
#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

#include "view/Game.hpp"

class Game;
class PlatformManager;
class GLFWwindow;

struct OpenGLRenderer
{
    int screenWidth;
    int screenHeight;
    float previousTimeSeconds;
    Game* pGame;
};

GLFWwindow* initializeOpenGLRenderer(int argc, char **argv, int screenWidth, int screenHeight, const string& gameName);
int mainLoopOpenGLRenderer(GLFWwindow* pWindow , Game* pGame, int screenWidth, int screenHeight, PlatformManager* pPlatformManager);

#endif /* OPENGLRENDERER_H */