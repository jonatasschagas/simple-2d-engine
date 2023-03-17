#include "SpriteFactory.hpp"
#include "data/DataCacheManager.hpp"

AnimatedSprite SpriteFactory::buildAnimatedSprite(
    string const& animationConfiguration) {
  AnimatedSpriteData const& rAnimatedSpriteData =
      DataCacheManager::getInstance()->getAnimatedSprite(
          animationConfiguration);
  SpritesheetData const& rSpritesheetData =
      DataCacheManager::getInstance()->getSprite(
          rAnimatedSpriteData.getConfigFile(),
          rAnimatedSpriteData.getTextureFile());
  return AnimatedSprite(rAnimatedSpriteData, rSpritesheetData);
}

Sprite SpriteFactory::buildSprite() { return Sprite(); }

TileMapSprite SpriteFactory::buildTileMapSprite(
    string const& tileMapConfiguration, string const& levelsLocation,
    string const& tileSetLocation, Vector2 const& tileSizeInWorldUnits,
    string const& metaLayerName) {
  TileMapData const& tileMapData =
      DataCacheManager::getInstance()->getTileMapData(
          tileMapConfiguration, levelsLocation, tileSetLocation);
  TileMapSprite tileMapSprite(tileSizeInWorldUnits, &tileMapData);
  return tileMapSprite;
}