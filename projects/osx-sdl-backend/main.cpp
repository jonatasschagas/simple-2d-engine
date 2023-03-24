
#include "SDLGame.hpp"
#include "SDLGraphicsManager.hpp"
#include "SDLSoundManager.hpp"
#include "SampleGame.hpp"

using namespace std;

int main(int argc, char** argv) {
  SDLGameConfigs sdlGameConfigs;
  sdlGameConfigs.windowTitle = "SDL Game";
  sdlGameConfigs.screenWidth = 640;
  sdlGameConfigs.screenHeight = 480;
  sdlGameConfigs.backgroundColor = {0, 0, 0, 255};

  SDLGame sdlGame(sdlGameConfigs);

  SDLGraphicsManager graphicsManager(sdlGame.getRenderer(),
                                     sdlGameConfigs.screenWidth,
                                     sdlGameConfigs.screenHeight);
  SDLSoundManager soundManager;

  SampleGame sampleGame(graphicsManager, soundManager);

  sdlGame.setGame(&sampleGame);

  int code = sdlGame.run();

  return code;
}
