### Getting started

In order to use this simple engine you must know C++ and CMake.

#### The Game Class

When using the engine you must define a type of **Game class**. The Game class is responsible for 
creating the **Views** of the game. Think of a view as a part of the game: main menu view, game view, settings view, etc.

The method *initialize* should be used to create the views of the game and add them to the framework. Your game class should
extend **view/Game.hpp**.

Here's an example of a Game class:

```cpp
#include "view/Game.hpp"
#include <string>

class SampleGame : public Game {
 public:
  SampleGame(GraphicsManager& rGraphicsManager, SoundManager& rSoundManager,
             InputManager& rInputManager);
  ~SampleGame() {}

  void initialize() override {
    GameView* pGameView = new GameView(); // creates the view
    addView("game-view", pGameView); // adds the view to the system, and transfers the ownership to it

    switchView("game-view"); // switches the view to be active
  }

  std::string const& getGameName() override { return  "Sample Game"; }
};

```

#### The View Class

The **View** classes are responsible for:

 - Creating the "scene graph" of game objects
 - Implementing the logic of the game for each frame **(update method)**
 - Reacting to Input from the player
 - Playing sounds/music
 - Switching to another *View* depending on the game logic

Your views should extend the class **view/View.h**. Checkout the class to see which methods can be overriden.

The **initialize** method should be used to create the game objects. The **update** method, should be used to run and execute the logic of the game.

Here's an example of a simple View:

```cpp
....
#include "view/View.h"

class GameView : public View {
 public:
  GameView(){}
  ~GameView(){}

  void initialize(ViewManager* pViewManager) override {
    addChild(&m_starField); // adds game object to the scene
    addChild(&m_rocket); // adds game object to the scene

    /* configures the game objects */
    m_starField.setXY(0, 0);
    m_starField.setSize(100.f, 100.f); // full screen size

    m_rocket.setXY(25.f, 50.f); 
    m_rocket.setSize(10.f, 15.f);

    m_pViewManager = pViewManager;  // view manager should be use to transition to other game views
  }


  // logic the game for each frame
  void update(float delta) {    
    if (m_speedToMove > 0) {
        m_rocket.moveRight();
    } else if (m_speedToMove < 0) {
        m_rocket.moveLeft();
    }
  }
  
  // reads input from the player
  void GameView::onKeyPressed(InputKey key) {
    switch (key) {
        case InputKey::KEY_LEFT:
        m_rocket.moveLeft();
        break;
        case InputKey::KEY_RIGHT:
        m_rocket.moveRight();
        break;
    }
  }
  // loads and plays music
  void processSounds(SoundManager& rSoundManager) override {
    if (!m_songInitialized) {
        string const& soundName = "assets/sounds/music.wav";
        rSoundManager.loadMusic(soundName);
        rSoundManager.playMusic(soundName);
        m_songInitialized = true;
    }
  }

 private:
  ....
};

```

#### The Sprites

The sprites are the "heart" of the engine. These types of classes are the game objects. Each of them have their own **render** and
**update** method. The render method is responsible for rendering the sprite on the screen and the update method is used define the logic of each game object.

Each Sprite has its own properties:
 - x and y position, set by **setXY**
 - width and height, set by **setSize**
 - rotation - measured in degrees, set by **setRotation**

Other noteworthy characteristics of a Sprite:
 - Sprites can have 0 or more children sprites. To add a sprite as a child of another, you should call the **addChild** method. Note: the ownership of the child is not of the parent sprite. **You should be responsible for deleting/cleaning sprites**.
 - When scaling, moving and/or rotating a parent Sprite, the children of that sprite are also affected accordingly, including their grandchildren sprites.
 - When calling **setXY** to update a Sprite's position, or **setSize** to update it's position, the values are percentage points relative to the parent of the Sprite, in the range of 0 to 100, where 100 means 100% of the size or position of the parent sprite.
 - Sprites have a pivot point that affects position and the rotation of the sprites.
 - There are 3 native types of Sprites:
    - **TexturedSprite**: used to display quads with a texture. **Note: Requires a shader called "textured" to be added to the GraphicsManager**
    - **ColoredSprite**: used to display quads with a solid color. **Note: Requires a shader called "colored" to be added to the GraphicsManager**
    - **StructuralSprite**: sprites that don't render but are used as a scaffold to aggregate children sprites.

You should extend one of these **Sprite** classes to create your own game objects. Here's an example:

```cpp

#include "core/TexturedSprite.hpp"

class Rocket : public TexturedSprite {
 public:
  
  Rocket(float speed) : TexturedSprite(), m_speed(speed) {  
    loadTexture("assets/images/rocket.png"); // loads the texture
    setWholeTexture(true);  // use the whole texture
    setRotation(90); // rotate the rocket by 90 degrees
  }

  ~Rocket() {}

  void update(float delta) override {
    TexturedSprite::update(delta);

    // logic for updating the rocket's position...

    if (m_originalY == 0.0f) {
        m_originalY = getY();
    }

    m_accumulatedDelta += delta;
    if (m_accumulatedDelta > m_speed) {
        
        float sinCal = sinf(degreesToRadians(m_angle));
        setXY(getX(), sinCal * 5.f + m_originalY);

        if (sinCal > 0) {
            setRotation(simple_lerp(getRotation(), 80, delta));
        } else {
            setRotation(simple_lerp(getRotation(), 100, delta));
        }

        m_angle += 1;
        if (m_angle > 360) {
            m_angle = 0;
        }
        m_accumulatedDelta = 0.0f;
    }

  }
  
  void moveLeft() {
    setXY(getX() - m_speed * 10, getY());
  }
  
  void moveRight() {    
    setXY(getX() + m_speed * 10, getY());
  }

 private:

  float m_speed = 0.05f;
  float m_accumulatedDelta = 0.0f;
  float m_originalY = 0.0f;
  int m_angle = 0;
};
```

### Creating the game

When creating the game, you must provide implementations of the following interfaces:
 - **graphics/GraphicsManager**: renders the game
 - **sounds/SoundManager**: plays sounds and music for the game
 - **disk/ResourcesManager**: provides access to read/write files in the underlying system
 - **input/InputManager**: reads input from the player

 Depending on your system, you should pick the appropriate implementation of each of the manager interfaces. You can find the implementations in the folder **service-implementation**.

 You must also provide the "main" loop (using your platform of preference) and call the **update** and **render** methods of your game class. 

 Here's an example of wiring up the engine and the game for running on OSX:

 ```cpp

    // resource provider
    OSXResourceProvider resourceProvider;
    
    // graphics manager
    OpenGLGraphicsManager openGLGraphicsManager(
      SCREEN_WIDTH, SCREEN_HEIGHT, WORLD_UNITS_X, dpiX, dpiY, resourceProvider);
    openGLGraphicsManager.initialize();

    // loading the shaders
    openGLGraphicsManager.loadShader("textured", "assets/shaders/osx/sprite.vs",
                                   "assets/shaders/osx/sprite.frag",
                                   resourceProvider);
    
    openGLGraphicsManager.loadShader("colored", "assets/shaders/osx/color.vs",
                                   "assets/shaders/osx/color.frag",
                                   resourceProvider);

    // input manager
    GLFWInputManager inputManager(*pWindow);

    // maps GLFW key codes to InputKey values
    inputManager.setKeyTranslatorFunction([](int key) -> InputKey {
        switch (key) {
        case GLFW_KEY_LEFT:
            return InputKey::KEY_LEFT;
        case GLFW_KEY_RIGHT:
            return InputKey::KEY_RIGHT;
        }
    });

    // sound manager
    SDLSoundManager sdlSoundManager;

    // the game
    SampleGame sampleGame(openGLGraphicsManager, sdlSoundManager, inputManager);

 ```

An example of main loop:

```cpp
  
  // initialize the game
  sampleGame.initialize();

  // DeltaTime variables
  GLfloat deltaTime = 0.0f;
  GLfloat lastFrame = 0.0f;

  while (!glfwWindowShouldClose(pWindow)) {
    
    // Calculate delta time
    GLfloat currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    sampleGame.update(deltaTime);

    inputManager.pollEvents();

    sampleGame.processSounds();

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    sampleGame.render();

    glfwSwapBuffers(pWindow);
    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
```

