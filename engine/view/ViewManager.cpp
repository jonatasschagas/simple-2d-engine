#include "ViewManager.hpp"

ViewManager::ViewManager(Vector2 const& screenSizeInGameUnits)
    : m_screenSizeInGameUnits(screenSizeInGameUnits) {
  initializeMembers();
}

ViewManager::~ViewManager() {
  // delete the views
  for (auto it = m_views.begin(); it != m_views.end(); ++it) {
    delete it->second;
  }

  initializeMembers();
}

void ViewManager::receiveEvent(Event* pEvent) {
  m_pCurrentView->receiveEvent(pEvent);
}

void ViewManager::render(GraphicsManager& rGraphicsManager) {
  if (m_pCurrentView != nullptr) {
    m_pCurrentView->render(rGraphicsManager);
  }
}

void ViewManager::processSounds(SoundManager& rSoundManager) {
  if (m_pCurrentView != nullptr) {
    m_pCurrentView->processSounds(rSoundManager);
  }
}

void ViewManager::readInput(int x, int y, bool pressed) {
  m_pCurrentView->readInput(x, y, pressed);
}

void ViewManager::update(float delta) {
  if (m_pCurrentView != nullptr) {
    m_pCurrentView->update(delta);
  }

  // safely deleting previous view now
  if (m_pPreviousView != nullptr) {
    delete m_pPreviousView;
    m_pPreviousView = nullptr;
  }
}

void ViewManager::updateEditor() { m_pCurrentView->updateEditor(); }

void ViewManager::switchView(string const& viewName) {
  if (m_views.find(viewName) != m_views.end()) {
    m_pCurrentView = m_views[viewName];
    m_pCurrentView->onEnter(nullptr);
  } else {
    printf("ViewManager::switchView: View %s not found)", viewName.c_str());
  }
}

void ViewManager::addView(string const& viewName, View* pView) {
  m_views[viewName] = pView;
  pView->setXY(0, 0);
  pView->setPivotAtCenter(true);
  pView->setSize(m_screenSizeInGameUnits.x, m_screenSizeInGameUnits.y);
  pView->initialize(this);
}
