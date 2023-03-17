#pragma once
#ifndef SDLGame_hpp
#define SDLGame_hpp

#include "SDL.h"
#include "SDLGraphicsManager.hpp"
#include "SDLSoundManager.hpp"
#include <stdio.h>
#include <string>

class Game;

struct SDLGameConfigs {
  std::string windowTitle;
  int screenWidth;
  int screenHeight;
  SDL_Color backgroundColor;
};

class SDLGame {
 public:
  SDLGame(SDLGameConfigs const& sdlGameConfigs, Game* pGame);
  ~SDLGame();

  int run();

 private:
  bool init();
  void handleInput(SDL_Event& sdlEvent);
  void handleInputOSX(SDL_Event& sdlEvent);
  void handleInputiOS(SDL_Event& sdlEvent);

  SDLGameConfigs const& m_sdlGameConfigs;
  bool m_clicked;

  // The window we'll be rendering to
  SDL_Window* m_pWindow;
  // The window renderer
  SDL_Renderer* m_pRenderer;
  SDL_Rect* m_pScreenRect;

  SDLGraphicsManager* m_pGraphicsManager;
  SDLSoundManager* m_pSoundManager;

  Game* m_pGame;

  void initializeMembers() {
    m_clicked = false;
    m_pWindow = nullptr;
    m_pRenderer = nullptr;
    m_pScreenRect = nullptr;
    m_pGame = nullptr;
    m_pGraphicsManager = nullptr;
    m_pSoundManager = nullptr;
  }
};

#endif /* SDLGame_hpp */
