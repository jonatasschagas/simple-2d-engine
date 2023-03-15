
#include "OSXResourceProvider.hpp"
#include "OpenGLGraphicsManager.hpp"
#include "OpenGLRenderer.h"
#include "SampleGame.hpp"
#include "platform/impl/MuteSoundManager.hpp"
#include <string>

using namespace std;

int main(int argc, char** argv) {
  int screenWidth = 800;
  int screenHeight = 600;

  // the game
  SampleGame sampleGame;

  GLFWwindow* pWindow = initializeOpenGLRenderer(
      argc, argv, screenWidth, screenHeight, sampleGame.getGameName());
  if (pWindow == nullptr)  // error on initialization
  {
    return -1;
  }

  OSXResourceProvider resourceProvider;

  string vertexShaderPath = "assets/shaders/osx/sprite.vs";
  string fragmentShaderPath = "assets/shaders/osx/sprite.frag";

  // platform manager can only be created after the OpenGL context is created
  OpenGLGraphicsManager openGLGraphicsManager(
      screenWidth, screenHeight, 100, resourceProvider, vertexShaderPath,
      fragmentShaderPath);
  openGLGraphicsManager.initialize();

  MuteSoundManager muteSoundManager;

  int code =
      mainLoopOpenGLRenderer(pWindow, sampleGame, screenWidth, screenHeight,
                             openGLGraphicsManager, muteSoundManager);

  return code;
}
