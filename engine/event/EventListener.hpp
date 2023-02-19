#pragma once
#ifndef EventListener_hpp
#define EventListener_hpp

#include <stdio.h>
#include "Event.hpp"

class EventListener
{
public:
    
    virtual void receiveEvent(Event* pEvent) = 0;
    
};

#endif /* EventListener_hpp */
