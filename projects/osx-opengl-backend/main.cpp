
#include "OSXResourceProvider.hpp"
#include "OpenGLGraphicsManager.hpp"
#include "OpenGLRenderer.h"
#include "SampleGame.hpp"
#include "platform/impl/MuteSoundManager.hpp"
#include <string>

using namespace std;

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 1024
#define WORLD_UNITS_X 100

int main(int argc, char** argv) {
  OSXResourceProvider resourceProvider;

  string vertexShaderPath = "assets/shaders/osx/sprite.vs";
  string fragmentShaderPath = "assets/shaders/osx/sprite.frag";

  string colorVertexShaderPath = "assets/shaders/osx/color.vs";
  string colorFragmentShaderPath = "assets/shaders/osx/color.frag";

  // the window
  GLFWwindow* pWindow = initializeOpenGLRenderer(argc, argv, SCREEN_WIDTH,
                                                 SCREEN_HEIGHT, "Sample Game");
  if (pWindow == nullptr) {
    return -1;
  }

  // platform manager can only be created after the OpenGL context is
  // created
  OpenGLGraphicsManager openGLGraphicsManager(
      SCREEN_WIDTH, SCREEN_HEIGHT, WORLD_UNITS_X, resourceProvider,
      vertexShaderPath, fragmentShaderPath, colorVertexShaderPath,
      colorFragmentShaderPath);
  openGLGraphicsManager.initialize();

  MuteSoundManager muteSoundManager;

  // the game
  SampleGame sampleGame(openGLGraphicsManager, muteSoundManager);

  int code = mainLoopOpenGLRenderer(pWindow, sampleGame);

  return code;
}
