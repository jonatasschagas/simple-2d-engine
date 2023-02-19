#include "ViewManager.hpp"

PlatformManager* ViewManager::getPlatformManager()
{
    return m_pPlatformManager;
}

void ViewManager::initialize(PlatformManager* pPlatformManager, DataCacheManager* pDataCacheManager) 
{
    m_pPlatformManager = pPlatformManager;
    m_pDataCacheManager = pDataCacheManager;
}

ViewManager::ViewManager()
{
    initializeMembers();
}

ViewManager::~ViewManager()
{
    // delete the views
    for (auto it = m_views.begin(); it != m_views.end(); ++it)
    {
        delete it->second;
    }
    
    initializeMembers();
}

void ViewManager::receiveEvent(Event* pEvent)
{
    m_pCurrentView->receiveEvent(pEvent);
}

void ViewManager::render()
{
    if (m_pCurrentView != nullptr) 
    {
        m_pCurrentView->render();
    }
}

void ViewManager::readInput(int x, int y, bool pressed)
{
	m_pCurrentView->readInput(x, y, pressed);
}

void ViewManager::update(float delta)
{
    if (m_pCurrentView != nullptr) 
    {
        m_pCurrentView->update(delta);
    }
    
	// safely deleting previous view now
	if (m_pPreviousView != nullptr)
	{
		delete m_pPreviousView;
		m_pPreviousView = nullptr;
	}
	
}

void ViewManager::updateEditor()
{
    m_pCurrentView->updateEditor();
}

void ViewManager::switchView(const string& viewName)
{

    if (m_views.find(viewName) != m_views.end())
    {
        m_pCurrentView = m_views[viewName];
        m_pCurrentView->onEnter(nullptr);
    }
    else
    {
        printf("ViewManager::switchView: View %s not found)", viewName.c_str());
    }
}

void ViewManager::addView(const string& viewName, View* pView)
{
    m_views[viewName] = pView;
    pView->initialize(this);
}

DataCacheManager* ViewManager::getDataCacheManager()
{
    return m_pDataCacheManager;
}