
#include "OpenGLGraphicsManager.hpp"
#include "OpenGLRenderer.h"
#include "SampleGame.hpp"
#include "platform/impl/MuteSoundManager.hpp"

int main(int argc, char** argv) {
  int screenWidth = 800;
  int screenHeight = 600;
  SampleGame sampleGame;

  GLFWwindow* pWindow = initializeOpenGLRenderer(
      argc, argv, screenWidth, screenHeight, sampleGame.getGameName());
  if (pWindow == nullptr)  // error on initialization
  {
    return -1;
  }

  // platform manager can only be created after the OpenGL context is created
  OpenGLGraphicsManager openGLGraphicsManager(screenWidth, screenHeight, 100);
  openGLGraphicsManager.initialize();

  MuteSoundManager muteSoundManager;

  int code =
      mainLoopOpenGLRenderer(pWindow, sampleGame, screenWidth, screenHeight,
                             openGLGraphicsManager, muteSoundManager);

  return code;
}
