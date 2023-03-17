
#include "SDLGame.hpp"
#include "SampleGame.hpp"

using namespace std;

int main(int argc, char** argv) {
  SDLGameConfigs sdlGameConfigs;
  sdlGameConfigs.windowTitle = "SDL Game";
  sdlGameConfigs.screenWidth = 640;
  sdlGameConfigs.screenHeight = 480;
  sdlGameConfigs.backgroundColor = {0, 0, 0, 255};

  SampleGame sampleGame;

  SDLGame sdlGame(sdlGameConfigs, &sampleGame);
  int code = sdlGame.run();

  return code;
}
