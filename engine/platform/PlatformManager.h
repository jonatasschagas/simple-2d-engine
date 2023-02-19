#pragma once
#ifndef PlatformRenderer_h
#define PlatformRenderer_h

#include <stdio.h>
#include <string>
#include "DrawCall.h"
#include "../core/Vector2.h"

using namespace std;

class PlatformManager
{
public:

    virtual void setOffsetY(float y) = 0;
    
    virtual void renderTexture(const DrawCall& drawCall) = 0;

    virtual void playSoundEffect(const string& name) = 0;
    virtual void playMusic(const string& path) = 0;
    virtual void stopSounds() = 0;
    
    virtual bool loadMusic(const string& path) = 0;
    virtual bool loadSoundEffect(const string& name, const string& path) = 0;
    virtual void* loadTexture(const string& path) = 0;
    
    virtual const int getWorldLocationXFromScreenCoordinates(int x) const = 0;
    virtual const int getWorldLocationYFromScreenCoordinates(int y) const = 0;
    
    virtual const Vector2 getScreenSizeInGameUnits() const = 0;
    virtual int getScreenWidth() const = 0;
    virtual int getScreenHeight() const = 0;
    
    virtual void setDebugMode(bool debugMode) = 0;
    virtual bool isDebugMode() const = 0;
    
    virtual unsigned int getTicks() const = 0;
    
    virtual bool shouldScale() const = 0;
    
    virtual ~PlatformManager() {}

};


#endif /* PlatformRenderer_h */
