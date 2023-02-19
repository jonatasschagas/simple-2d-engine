#pragma once
#ifndef SDLManager_hpp
#define SDLManager_hpp

#include <stdio.h>
#include <vector>
#include <map>
#include <string>
#include "SDL.h"
#include "LTexture.hpp"
#include "SDL_mixer.h"
#include "../engine/platform/PlatformManager.h"

using namespace std;

struct RGBA
{
    int r,g,b,a;
};

class SDLManager : public PlatformManager
{
public:
    
    void init(SDL_Renderer* pRenderer, int screenWidth, int screenHeight);
    
    void renderText(const string& labelName, float worldX, float worldY, float scaleX=1, float scaleY=1);
    void renderTexture(const DrawCall& drawCall) override;
    void setOffsetY(float y) override;
    
    void renderDebugQuad(float worldX, float worldY, float width, float height, RGBA rgba, bool topToDown=false, bool scale=true);
    void renderFillQuad(float worldX, float worldY, float width, float height, RGBA rgba, bool topToDown=false, bool scale=true);
    void renderPolygon(const DrawCall& drawCall);
    void renderLines(const DrawCall& drawCall);
    void renderPoint(const DrawCall& drawCall);

    void playSoundEffect(const string& name) override;
    void playMusic(const string& path) override;
	void stopSounds() override;
    
    bool loadMusic(const string& path) override;
    bool loadSoundEffect(const string& name, const string& path) override;
    void* loadTexture(const string& path) override;
    bool loadText(const string& labelName, string text, int red, int green, int blue, int size);
    
    const int getWorldLocationXFromScreenCoordinates(int x) const override;
    const int getWorldLocationYFromScreenCoordinates(int y) const override;
    
    const Vector2 getScreenSizeInGameUnits() const override;
    bool shouldScale() const override;
    
    int getScreenWidth() const override;
    int getScreenHeight() const override;

    static SDLManager* getInstance()
    {
        if(!sm_pInstance)
        {
            sm_pInstance = new SDLManager();
        }
        return sm_pInstance;
    }
    
    SDLManager(SDLManager const&) = delete;
    void operator=(SDLManager const&) = delete;
    
    void setDebugMode(bool debugMode) override;
    bool isDebugMode() const override;
    
	unsigned int getTicks() const override;
	
    ~SDLManager();
    
private:
    
    static SDLManager* sm_pInstance;
    
    SDLManager() {
        initializeMembers();
    }
    
    SDL_Renderer* m_pRenderer;
    vector<LTexture*> m_textures;
    vector<string> m_texturesNames;
    map<string,int> m_textureMap;
    map<string,Mix_Chunk*> m_soundEffects;
    map<string,Mix_Music*> m_songs;
    int m_screenWidth;
    int m_screenHeight;
    float m_scaleFactorX;
    float m_scaleFactorY;
    float m_currentOffsetY;
    int m_screenWidthInGameUnits;
    int m_screenHeightInGameUnits;
    bool m_debugMode;
	bool m_sounds;
    
    void initializeMembers()
    {
        m_pRenderer = NULL;
        m_textures.clear();
        m_texturesNames.clear();
        m_textureMap.clear();
        m_soundEffects.clear();
        m_songs.clear();
        m_scaleFactorX = 0.f;
        m_scaleFactorY = 0.f;
        m_screenWidthInGameUnits = 0;
        m_screenHeightInGameUnits = 0;
        m_currentOffsetY = 0;
        m_debugMode = false;
		m_sounds = true;
    }
    
};

#endif /* SDLManager_hpp */
