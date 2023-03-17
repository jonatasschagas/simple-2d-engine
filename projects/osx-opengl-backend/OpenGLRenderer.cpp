#include "OpenGLRenderer.h"
#include "OpenGLHeaders.h"
#include "view/Game.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

Game* pGame = nullptr;

void render(Game& rGame, GraphicsManager& rGraphicsManager) {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  rGame.render(rGraphicsManager);
}

void framebufferSizeCallback(GLFWwindow* pWindow, int width, int height) {
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* pWindow) {
  if (glfwGetKey(pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(pWindow, true);
  }
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action,
                 int mods) {
  if (pGame == nullptr) return;
  if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
    Event v("right-start");
    pGame->receiveEvent(&v);
  } else if (key == GLFW_KEY_LEFT && action == GLFW_PRESS) {
    Event v("left-start");
    pGame->receiveEvent(&v);
  } else if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
    Event v("up-start");
    pGame->receiveEvent(&v);
  } else if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
    Event v("down-start");
    pGame->receiveEvent(&v);
  }
  if (key == GLFW_KEY_RIGHT && action == GLFW_RELEASE) {
    Event v("right-end");
    pGame->receiveEvent(&v);
  } else if (key == GLFW_KEY_LEFT && action == GLFW_RELEASE) {
    Event v("left-end");
    pGame->receiveEvent(&v);
  } else if (key == GLFW_KEY_UP && action == GLFW_RELEASE) {
    Event v("up-end");
    pGame->receiveEvent(&v);
  } else if (key == GLFW_KEY_DOWN && action == GLFW_RELEASE) {
    Event v("down-end");
    pGame->receiveEvent(&v);
  }
}

GLFWwindow* initializeOpenGLRenderer(int argc, char** argv, int screenWidth,
                                     int screenHeight, string const& gameName) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  GLFWwindow* pWindow =
      glfwCreateWindow(screenWidth, screenHeight, gameName.c_str(), NULL, NULL);
  if (pWindow == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return nullptr;
  }
  glfwMakeContextCurrent(pWindow);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return nullptr;
  }

  glViewport(0, 0, screenWidth, screenHeight);
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glfwSetFramebufferSizeCallback(pWindow, framebufferSizeCallback);
  glfwSetKeyCallback(pWindow, keyCallback);

  return pWindow;
}

int mainLoopOpenGLRenderer(GLFWwindow* pWindow, Game& rGame, int screenWidth,
                           int screenHeight, GraphicsManager& rGraphicsManager,
                           SoundManager& rSoundManager) {
  pGame = &rGame;
  rGame.initialize(rGraphicsManager.getScreenSizeInGameUnits());

  // DeltaTime variables
  GLfloat deltaTime = 0.0f;
  GLfloat lastFrame = 0.0f;

  while (!glfwWindowShouldClose(pWindow)) {
    // Calculate delta time
    GLfloat currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    rGame.update(deltaTime);

    processInput(pWindow);

    render(rGame, rGraphicsManager);

    glfwSwapBuffers(pWindow);
    glfwPollEvents();
  }

  glfwTerminate();

  return 0;
}
