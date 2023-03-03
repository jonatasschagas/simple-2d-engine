#pragma once
#ifndef DrawCall_h
#define DrawCall_h

#include <stdio.h>
#include <string>
#include <vector>
#include "core/Vector2.h"

using namespace std;

struct Color
{
    float r;
    float g;
    float b;
    float a;

    Color(float _r, float _g, float _b, float _a) : r(_r), g(_g), b(_b), a(_a) {};
    Color(){};

};

struct ColorReplacement
{
    bool colorFilter=false;
    Color colorKey;
    Color colorReplacement;
    float threshold;
};

struct TextureSettings
{
    string name = "";
    int x;
    int y;
    int w;
    int h;
    float alpha;
};

struct SpriteProperties
{
    float x;
    float y;
    float w;
    float h;
    float rotation;
};

struct Vertex
{
    Vertex(Vector2 _position, Vector2 _textureCoordinates, Color _color) : 
        position(_position), textureCoordinates(_textureCoordinates), color(_color) {}
    Vertex(Vector2 _position, Color _color) : position(_position), color(_color) {}
    Vertex(){};

    Vector2 position;
    Vector2 textureCoordinates;
    Color color;
};

struct Settings
{
    bool flipHorizontal=false;
    bool topToDown=false;
    bool scale=true;
    bool tileMap=false;
    bool font=false;
};

class DrawCall
{
public:
    Settings settings;
    SpriteProperties spriteProperties;
    TextureSettings textureSettings;
    ColorReplacement colorReplacement1;
    ColorReplacement colorReplacement2;
    Color color;
    bool debug;
    bool colored;
    vector<Vertex> vertices;
    vector<Vertex> lines;
    Vertex point;
};

inline TextureSettings makeTextureSettings(const string& textureName, int tx, int ty, int tw, int th, float alpha=1.0f)
{
    TextureSettings textureSettings;
    textureSettings.name = textureName;
    textureSettings.x = tx;
    textureSettings.y = ty;
    textureSettings.w = tw;
    textureSettings.h = th;
    textureSettings.alpha = alpha;
    return textureSettings;
}

inline Color makeColor(float r, float g, float b, float a)
{
    Color color;
    color.r = r;
    color.g = g;
    color.b = b;
    color.a = a;
    
    return color;
}

inline ColorReplacement makeColorReplacement( bool colorFilter,
                                        Color key,
                                        Color replacement,
                                        float threshold)
{
    ColorReplacement bgFilterSettings;
    bgFilterSettings.colorFilter = colorFilter;
    bgFilterSettings.colorKey = key;
    bgFilterSettings.colorReplacement = replacement;
    bgFilterSettings.threshold = threshold;
    return bgFilterSettings;
}

inline SpriteProperties makeSpriteProperties(float x,
                                             float y,
                                             float w,
                                             float h,
                                             float rotation=0.0f)
{
    SpriteProperties spriteProperties;
    spriteProperties.x = x;
    spriteProperties.y = y;
    spriteProperties.w = w;
    spriteProperties.h = h;
    spriteProperties.rotation = rotation;
    
    return spriteProperties;
}

inline Settings makeSettings(bool flipHorizontal=false,
                      bool topToDown=false,
                      bool scale=true,
                      bool tileMap=false,
                      bool font=false)
{
    Settings settings;
    settings.flipHorizontal = flipHorizontal;
    settings.topToDown = topToDown;
    settings.scale = scale;
    settings.tileMap = tileMap;
    settings.font = font;
    
    return settings;
}

#endif /* DrawCall_h */
