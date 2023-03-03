#pragma once

#ifndef SampleGame_hpp
#define SampleGame_hpp

#include <string>

#include "view/Game.hpp"
#include "view/ViewManager.hpp"
#include "data/DataCacheManager.hpp"

using namespace std;

class SampleGame : public Game
{
public:
    
    SampleGame();
    ~SampleGame();
    
    void initialize(PlatformManager* pManager) override;
    void receiveEvent(Event* pEvent) override;
    void update(const float deltaTime) override;
    void updateEditor(const float deltaTime) override;
    void render() override;
    const string& getGameName() override;

private:

    PlatformManager* m_pPlatformManager;
    DataCacheManager m_dataCacheManager;
    ViewManager m_viewManager;
    string m_gameName;

    void initializeMembers()
    {
        m_pPlatformManager = nullptr;
        m_gameName = "Sample Game";
    }

};

#endif /* SampleGame_hpp */