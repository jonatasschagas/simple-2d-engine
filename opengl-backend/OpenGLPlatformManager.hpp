#pragma once
#ifndef OpenGLPlatformManager_hpp
#define OpenGLPlatformManager_hpp

#include "platform/PlatformManager.h"
#include "SpriteRenderer.hpp"

class OpenGLPlatformManager : public PlatformManager
{
public:
    
    OpenGLPlatformManager(int screenWidth, int screenHeight, int screenWidthInGameUnits);
    ~OpenGLPlatformManager();

    void initialize() override;
    
    void setOffsetY(float y) override;
    
    void renderTexture(const DrawCall& drawCall) override;

    void playSoundEffect(const string& name) override;
    void playMusic(const string& path) override;
    void stopSounds() override;
    
    bool loadMusic(const string& path) override;
    bool loadSoundEffect(const string& name, const string& path) override;
    void* loadTexture(const string& path) override;
    
    const int getWorldLocationXFromScreenCoordinates(int x) const override;
    const int getWorldLocationYFromScreenCoordinates(int y) const override;
    
    const Vector2 getScreenSizeInGameUnits() const override;
    int getScreenWidth() const override;
    int getScreenHeight() const override;
    
    void setDebugMode(bool debugMode) override;
    bool isDebugMode() const override;
    
    unsigned int getTicks() const override;
    
    bool shouldScale() const override;

private:

    SpriteRenderer m_spriteRenderer;
    float m_offsetY;
    int m_screenWidth;
    int m_screenHeight;
    int m_screenWidthInGameUnits;
    int m_screenHeightInGameUnits;
    float m_scaleFactorX;
    float m_scaleFactorY;
    bool m_debugMode;

    void initializeMembers()
    {
        m_offsetY = 0.0f;
        m_screenWidth = 0;
        m_screenHeight = 0;
        m_screenWidthInGameUnits = 0;
        m_screenHeightInGameUnits = 0;
        m_scaleFactorX = 0;
        m_scaleFactorY = 0;
        m_debugMode = false;
    }

};

#endif /* OpenGLPlatformManager_hpp */