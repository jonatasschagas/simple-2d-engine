#include "OpenGLRenderer.h"
#include "OpenGLHeaders.h"
#include "view/Game.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

OpenGLRenderer openGLRenderer;

void render(Game& rGame, GraphicsManager& rGraphicsManager) {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  rGame.render(rGraphicsManager);
}

void framebuffer_size_callback(GLFWwindow* pWindow, int width, int height) {
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* pWindow) {
  if (glfwGetKey(pWindow, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(pWindow, true);
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

  glfwSetFramebufferSizeCallback(pWindow, framebuffer_size_callback);

  return pWindow;
}

int mainLoopOpenGLRenderer(GLFWwindow* pWindow, Game& rGame, int screenWidth,
                           int screenHeight, GraphicsManager& rGraphicsManager,
                           SoundManager& rSoundManager) {
  rGame.initialize();

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
