#pragma once
#ifndef Sprite_hpp
#define Sprite_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include "glm/glm.hpp"
#include "Vector2.h"
#include "platform/DrawCall.h"
#include "platform/PlatformManager.h"

using namespace std;

class Sprite
{
public:
    
    Sprite(PlatformManager* pPlatformManager);
    virtual ~Sprite();
    
    void loadTexture(const string& textureFileName);
    
    void playSoundEffect(const string& soundName);

    void setX(float x);
    void setY(float y);
    void setXY(float x, float y);
    void setXYInvertedY(float x, float y);
    void setPosition(const Vector2& position);
    void setSize(float w, float h);
    void setSize(const Vector2& size);
    void setTextureCoordinates(float x, float y, float w, float h);
    void setScale(float scaleLevel);
    void setRotation(float degrees);
    void setTextureRotation(float degrees);
    void setPivotAtCenter(bool pivotAtCenter);
    void setCenteredOnParentX(bool centeredOnParentX) { m_centeredOnParentX = centeredOnParentX; }
    void setCenteredOnParentY(bool centeredOnParentY) { m_centeredOnParentY = centeredOnParentY; }
    void setDebugSprite(const bool debugSprite) { m_debugSprite = debugSprite; }
    
    const glm::vec2& getUntransformedCoordinates() const { return m_coords; };
    float getX() const { return m_coords.x; }
    float getY() const { return m_coords.y; }
    const Vector2 getSize() const { return Vector2(m_size.x, m_size.y); };
    float getTransformedX() const { return m_points[0].x; }
    float getTransformedY() const { return m_points[0].y; }
    Vector2 getScreenPosition() { return Vector2(getTransformedX(), getTransformedY()); }
    Vector2 getGamePosition() { return Vector2(m_coords.x, m_coords.y); }
    float getWidth() const { return m_points[1].x - m_points[0].x; }
    float getHeight() const { return m_points[1].y - m_points[0].y; }
    
    void setColor(float r, float g, float b);
    void setColorAlpha(float a) {m_a = a;}
    
    void fillParent() { setSize(m_pParent->getSize().x, m_pParent->getSize().y);}
    
    const bool isFlipped() const { return m_flip; };
    
    void setAlpha(const float alpha);
    void setFlip(const bool flip) { m_flip = flip; }
    void setTileMap(const bool tileMap) { m_tileMap = tileMap; }
    void addChild(Sprite* pChild);
    void setVisible(bool visible) { m_visible = visible; };
    bool isVisible() const { return m_visible; };
    
    virtual void update(float deltaTime);
    virtual void render();
    
    const std::vector<Sprite*>& getChildren() const { return m_children; };
    void removeChild(const int index);
    void removeChild(Sprite* pChildToRemove);
    void removeChildForced(Sprite* pChildToRemove);
    void removeAllChildren();

    void destroy();
    
    virtual bool isVisibleInParent(Sprite* pChild) const;
    bool hasTexture() const { return m_textureFilename.size() > 0; };
    
    void setSortChildren(bool sortChildren) { m_sortChildren = sortChildren; }
    PlatformManager* getPlatformManager() const { return m_pPlatformManager; }
    
    void setVertices(vector<Vertex>& vertices);

    Sprite* getParent() const { return m_pParent; }

protected:
    
    Sprite* m_pParent;
    glm::vec2 m_size;
    float m_alpha;
    
private:
    
    PlatformManager* m_pPlatformManager;

    glm::vec2 m_coords;
    
    glm::mat4 calculateTransform(Sprite* pSprite);
    
    string m_textureFilename;
    
    bool m_centeredOnParentX;
    bool m_centeredOnParentY;
    bool m_pivotCentered;
    bool m_visible;
    float m_angle;
    
    glm::vec4 m_points[2];
    glm::vec4 m_textureCoordinates;
    bool m_flip;
    bool m_tileMap;
    bool m_debugSprite;
    
    DrawCall* m_pDrawCall;
        
    glm::mat4 m_worldTransform;
    glm::mat4 m_transform;
    glm::mat4 m_rotation;
    glm::mat4 m_scale;
    
    std::vector<Sprite*> m_children;
    std::vector<Sprite*> m_childrenToRemove;

    bool m_coloredSprite;
    float m_r;
    float m_g;
    float m_b;
    float m_a;

    bool m_sortChildren;
    
    void initializeMembers()
	{
        m_textureFilename = "";
        m_alpha = 1.f;
        m_angle = 0;
    	m_pParent = nullptr;
        m_pDrawCall = nullptr;
        m_flip = false;
		m_children.clear();
        m_pivotCentered = false;
        m_centeredOnParentX = false;
        m_centeredOnParentY = false;
        m_visible = true;
        m_debugSprite = false;

        m_coords.x = 0;
        m_coords.y = 0;
        m_size.x = 0;
        m_size.y = 0;
        
        m_coloredSprite = false;
        m_r = 0;
        m_g = 0;
        m_b = 0;
        m_a = 0;
        m_sortChildren = false;

        m_textureCoordinates.x = 0;
        m_textureCoordinates.y = 0;
        m_textureCoordinates.z = 0;
        m_textureCoordinates.w = 0;
	}

};

#endif /* Sprite_hpp */
