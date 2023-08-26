#pragma once
#ifndef SpriteFactory_hpp
#define SpriteFactory_hpp

#include "AnimatedSprite.hpp"
#include "Sprite.hpp"
#include "TileMapSprite.hpp"
#include "Vector2.h"
#include <string>

using namespace std;

class SpriteFactory {
 public:
  static AnimatedSprite buildAnimatedSprite(
      string const& animationConfiguration);

  static Sprite buildSprite();
    
  static Sprite buildSimpleTexturedSprite(string const& texturePath);

  static TileMapSprite buildTileMapSprite(string const& tileMapConfiguration,
                                          string const& levelsLocation,
                                          string const& tileSetLocation,
                                          Vector2 const& tileSizeInWorldUnits,
                                          string const& metaLayerName);
};

#endif /* SpriteFactory_hpp */
