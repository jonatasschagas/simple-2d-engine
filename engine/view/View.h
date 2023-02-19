#ifndef View_h
#define View_h

#include "../core/Sprite.hpp"
#include "../event/EventListener.hpp"

class ViewManager;

class View : public EventListener, public Sprite
{
public:
    
    View(PlatformManager* pPlatformManager) : Sprite(pPlatformManager) {};
    virtual ~View(){};

	virtual void initialize(ViewManager* pViewManager) = 0;
    virtual void receiveEvent(Event* pEvent) = 0;
    virtual void readInput(int x, int y, bool pressed) = 0;
    virtual void updateEditor() = 0;
    virtual void onEnter(void* param) {};
    
};


#endif /* View_h */
