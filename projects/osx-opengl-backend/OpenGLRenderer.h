#pragma once

#ifndef OPENGLRENDERER_H
#define OPENGLRENDERER_H

class Game;

struct OpenGLRenderer
{
    int screenWidth;
    int screenHeight;
    float previousTimeSeconds;
    Game* pGame;
};

#include "OpenGLRenderer.h"

#include "view/Game.hpp"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

void render();

void resizeWindow(int w, int h);

void update();

void initialize(int argc, char **argv, Game* pGame, int screenWidth, int screenHeight);

#endif /* OPENGLRENDERER_H */