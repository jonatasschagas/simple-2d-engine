#ifndef Game_hpp
#define Game_hpp

#include "event/EventListener.hpp"
#include "platform/PlatformManager.h"

class Game : public EventListener
{
public:

    virtual ~Game(){};
    
    virtual void initImGui() {};
	virtual void initialize(PlatformManager* pManager) = 0;
    virtual void receiveEvent(Event* pEvent) = 0;
    virtual void update(const float deltaTime) = 0;
    virtual void updateEditor(const float deltaTime) = 0;
    virtual void render() = 0;

};


#endif /* Game_hpp */
