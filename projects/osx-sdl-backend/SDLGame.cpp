#include "SDLGame.hpp"
#include "LTimer.hpp"
#include "SDLResourceProvider.hpp"
#include "SDL_image.h"
#include "SDL_mixer.h"
#include "data/DataCacheManager.hpp"
#include "event/Event.hpp"
#include "view/Game.hpp"

int const SCREEN_FPS = 60;
int const SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

SDLGame::SDLGame(SDLGameConfigs const& sdlGameConfigs, Game* pGame)
    : m_sdlGameConfigs(sdlGameConfigs) {
  initializeMembers();

  m_pGame = pGame;
}

SDLGame::~SDLGame() {
  delete m_pScreenRect;
  delete m_pGraphicsManager;
  delete m_pSoundManager;

  // Destroy window
  SDL_DestroyRenderer(m_pRenderer);
  SDL_DestroyWindow(m_pWindow);
  m_pWindow = NULL;
  m_pRenderer = NULL;

  // Quit SDL subsystems
  Mix_Quit();
  IMG_Quit();
  SDL_Quit();

  initializeMembers();
}

bool SDLGame::init() {
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
    printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    return false;
  } else {
    // Screen dimensions
    m_pScreenRect = new SDL_Rect();

    // resolution for mac os x
#ifdef TARGET_OS_OSX
    m_pScreenRect->w = m_sdlGameConfigs.screenWidth;
    m_pScreenRect->h = m_sdlGameConfigs.screenHeight;
#else
    // Get device display mode
    SDL_DisplayMode displayMode;
    if (SDL_GetCurrentDisplayMode(0, &displayMode) == 0) {
      m_pScreenRect->w = displayMode.w;
      m_pScreenRect->h = displayMode.h;
    } else {
      printf("Could not get proper screen resolution! SDL Error: %s\n",
             SDL_GetError());
      return false
    }
#endif

    // Set texture filtering to linear
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0")) {
      printf("Warning: Linear texture filtering not enabled!");
    }

    // Create window
    Uint32 windowFlags = SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI;

// disable high DPI for mac osx (for click coordinates calculations)
#ifdef TARGET_OS_OSX
    windowFlags = SDL_WINDOW_SHOWN;
#endif

    m_pWindow =
        SDL_CreateWindow(m_sdlGameConfigs.windowTitle.c_str(),
                         SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                         m_pScreenRect->w, m_pScreenRect->h, windowFlags);
    if (m_pWindow == NULL) {
      printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
      return false;
    } else {
      // Create renderer for window
      m_pRenderer = SDL_CreateRenderer(
          m_pWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
      if (m_pRenderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n",
               SDL_GetError());
        return false;
      } else {
        // Initialize renderer color
        SDL_SetRenderDrawColor(m_pRenderer, 0, 0, 0, 0);

        // Initialize PNG loading
        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags)) {
          printf("SDL_image could not initialize! SDL_image Error: %s\n",
                 IMG_GetError());
          return false;
        }

        // Initialize SDL_mixer
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
          printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n",
                 Mix_GetError());
          return false;
        }
      }

      // enabling alpha
      SDL_SetRenderDrawBlendMode(m_pRenderer, SDL_BLENDMODE_BLEND);

      // update screen size
      SDL_GetRendererOutputSize(m_pRenderer, &m_pScreenRect->w,
                                &m_pScreenRect->h);
    }

    m_pGraphicsManager =
        new SDLGraphicsManager(m_pRenderer, m_pScreenRect->w, m_pScreenRect->h);
    m_pSoundManager = new SDLSoundManager();

    // initializing the game
    int screenWidthInGameUnits = 100;
    float aspectRatio = m_pScreenRect->w / (m_pScreenRect->h * 1.f);
    // the number of vertical units depends on the aspect ratio of the device
    int screenHeightInGameUnits = ceil(screenWidthInGameUnits / aspectRatio);

    DataCacheManager::getInstance()->setResourceProvider(
        new SDLResourceProvider());

    m_pGame->initialize(
        Vector2(screenWidthInGameUnits, screenHeightInGameUnits));
  }

  return true;
}

int SDLGame::run() {
  // Start up SDL and create window
  if (!init()) {
    printf("Failed to initialize!\n");
    return 1;
  } else {
    // Main loop flag
    bool quit = false;

    // Event handler
    SDL_Event sdlEvent;

    // The frames per second timer
    LTimer fpsTimer;

    // The frames per second cap timer
    LTimer capTimer;

    // Start counting frames per second
    fpsTimer.start();

    // While application is running
    while (!quit) {
      // Start cap timer
      capTimer.start();

      // Handle events on queue
      while (SDL_PollEvent(&sdlEvent) != 0) {
        // User requests quit
        if (sdlEvent.type == SDL_QUIT) {
          return 0;
        }

        handleInput(sdlEvent);
      }

      // Calculate time step`
      float timeStep = fpsTimer.getTicks() / 1000.f;
      if (timeStep > 0.16f) {
        timeStep = 0.16f;
      }

      m_pGame->update(timeStep);

      // Clear screen
      SDL_RenderClear(m_pRenderer);

      // Clear screen
      SDL_SetRenderDrawColor(m_pRenderer, m_sdlGameConfigs.backgroundColor.r,
                             m_sdlGameConfigs.backgroundColor.g,
                             m_sdlGameConfigs.backgroundColor.b,
                             m_sdlGameConfigs.backgroundColor.a);
      SDL_RenderClear(m_pRenderer);

      // RENDERING
      m_pGame->render(*m_pGraphicsManager);

      // SOUNDS
      m_pGame->processSounds(*m_pSoundManager);

      m_pGame->updateEditor(timeStep);

      // Update screen
      SDL_RenderPresent(m_pRenderer);

      int frameTicks = capTimer.getTicks();
      if (frameTicks < SCREEN_TICKS_PER_FRAME) {
        // Wait remaining time
        SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
      }
    }
  }

  return 0;
}

void SDLGame::handleInput(SDL_Event& sdlEvent) {
#ifdef TARGET_OS_OSX
  handleInputOSX(sdlEvent);
#endif

#ifdef TARGET_OS_IOS
  handleInputiOS(sdlEvent);
#endif
}

void SDLGame::handleInputOSX(SDL_Event& sdlEvent) {
  Event event;
  event.setTarget("player");
  Uint8 const* currentKeyStates = SDL_GetKeyboardState(NULL);

  if (sdlEvent.type == SDL_KEYDOWN) {
    if (currentKeyStates[SDL_SCANCODE_LEFT]) {
      event.setName("left_start");
      m_pGame->receiveEvent(&event);
    } else if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
      event.setName("right_start");
      m_pGame->receiveEvent(&event);
    }

    if (currentKeyStates[SDL_SCANCODE_UP]) {
      event.setName("up_start");
      m_pGame->receiveEvent(&event);
    } else if (currentKeyStates[SDL_SCANCODE_DOWN]) {
      event.setName("down_start");
      m_pGame->receiveEvent(&event);
    }

    if (currentKeyStates[SDL_SCANCODE_SPACE]) {
      event.setName("space_start");
      m_pGame->receiveEvent(&event);
    }

    if (currentKeyStates[SDL_SCANCODE_D]) {
      event.setName("debug_toggle");
      m_pGame->receiveEvent(&event);
    }
  } else if (sdlEvent.type == SDL_KEYUP) {
    SDL_Scancode scanCode = sdlEvent.key.keysym.scancode;

    if (scanCode == SDL_SCANCODE_DOWN) {
      event.setName("down_stop");
      m_pGame->receiveEvent(&event);
    } else if (scanCode == SDL_SCANCODE_UP) {
      event.setName("up_stop");
      m_pGame->receiveEvent(&event);
    }

    if (scanCode == SDL_SCANCODE_LEFT) {
      event.setName("left_stop");
      m_pGame->receiveEvent(&event);
    } else if (scanCode == SDL_SCANCODE_RIGHT) {
      event.setName("right_stop");
      m_pGame->receiveEvent(&event);
    }

    if (scanCode == SDL_SCANCODE_SPACE) {
      event.setName("space_stop");
      m_pGame->receiveEvent(&event);
    } else if (scanCode == SDL_SCANCODE_P) {
      event.setName("pause");
      m_pGame->receiveEvent(&event);
    }

  } else if (sdlEvent.type == SDL_MOUSEBUTTONUP ||
             sdlEvent.type == SDL_MOUSEBUTTONDOWN) {
    int x, y;
    SDL_GetMouseState(&x, &y);
    m_clicked = sdlEvent.type == SDL_MOUSEBUTTONDOWN;

    Event touchInputEvent(m_clicked ? "touch_start" : "touch_stop");
    touchInputEvent.setInputCoordinates(Vector2(x, y));
    m_pGame->receiveEvent(&touchInputEvent);
  }
}

void SDLGame::handleInputiOS(SDL_Event& sdlEvent) {
  if (sdlEvent.type != SDL_FINGERDOWN && sdlEvent.type != SDL_FINGERUP) {
    return;
  }

  bool pressed = sdlEvent.type == SDL_FINGERDOWN;
  SDL_TouchFingerEvent fingerEvent = sdlEvent.tfinger;
  Event touchInputEvent(pressed ? "touch_start" : "touch_stop");
  touchInputEvent.setInputCoordinates(Vector2(
      fingerEvent.x * m_pScreenRect->w, fingerEvent.y * m_pScreenRect->h));
  m_pGame->receiveEvent(&touchInputEvent);
}
