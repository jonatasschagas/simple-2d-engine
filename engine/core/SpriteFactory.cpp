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
