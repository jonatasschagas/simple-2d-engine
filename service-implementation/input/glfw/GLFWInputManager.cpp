#include "GLFWInputManager.hpp"

GLFWInputManager::GLFWInputManager(GLFWwindow& rWindow) : m_rWindow(rWindow) {}

GLFWInputManager::~GLFWInputManager() {}

void GLFWInputManager::pollEvents() {
  // poll for events
  glfwPollEvents();

  static std::vector<int> lastKeyState(GLFW_KEY_LAST,
                                       GLFW_RELEASE);  // track last key state

  if (m_keyTranslatorFunction) {
    // check for key events
    for (int i = 0; i < GLFW_KEY_LAST; i++) {
      int currentState = glfwGetKey(&m_rWindow, i);

      if (currentState == GLFW_PRESS && lastKeyState[i] == GLFW_RELEASE) {
        m_pInputListener->onKeyPressed(m_keyTranslatorFunction(i));
      } else if (currentState == GLFW_RELEASE &&
                 lastKeyState[i] == GLFW_PRESS) {
        m_pInputListener->onKeyReleased(m_keyTranslatorFunction(i));
      }

      // Update the last known state
      lastKeyState[i] = currentState;
    }
  }

  // check for mouse events
  double mouseX, mouseY;
  glfwGetCursorPos(&m_rWindow, &mouseX, &mouseY);
  m_pInputListener->onMouseMoved((int)mouseX, (int)mouseY);

  if (glfwGetMouseButton(&m_rWindow, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
    m_pInputListener->onMousePressed((int)mouseX, (int)mouseY);
  } else if (glfwGetMouseButton(&m_rWindow, GLFW_MOUSE_BUTTON_LEFT) ==
             GLFW_RELEASE) {
    m_pInputListener->onMouseReleased((int)mouseX, (int)mouseY);
  }
}