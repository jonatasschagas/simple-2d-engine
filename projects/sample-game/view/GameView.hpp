#pragma once
#ifndef GameView_hpp
#define GameView_hpp

#include "view/View.h"
#include "core/AnimatedSprite.hpp"
#include "platform/PlatformManager.h"
#include "data/DataCacheManager.hpp"

class GameView : public View
{
public:
    
    GameView(PlatformManager& rPlatformManager, DataCacheManager& rDataCacheManager);
    ~GameView();
    
    void initialize(ViewManager* pViewManager) override;
    virtual void receiveEvent(Event* pEvent) override;
    virtual void readInput(int x, int y, bool pressed) override;
    virtual void updateEditor() override;

private:

    AnimatedSprite m_characterSprite;
    PlatformManager& m_rPlatformManager;
    DataCacheManager& m_rDataCacheManager;

};

#endif /* GameView_hpp */