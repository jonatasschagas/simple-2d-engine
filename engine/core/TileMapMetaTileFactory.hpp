#pragma once
#ifndef TileMapMetaTileFactory_H
#define TileMapMetaTileFactory_H

#include "Sprite.hpp"
#include "data/TileMapData.hpp"

class TileMapMetaTileFactory
{
public:

    virtual ~TileMapMetaTileFactory() {}
    
    virtual Sprite* createMetaTile(const int tileX, const int tileY, const TileConfig* pTileConfig, const Vector2& position, const Vector2& size) = 0;

};

#endif //TileMapMetaTileFactory_H
