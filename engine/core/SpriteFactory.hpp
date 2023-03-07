#pragma once
#ifndef SpriteFactory_hpp
#define SpriteFactory_hpp

#include "AnimatedSprite.hpp"
#include "Sprite.hpp"
#include <string>

using namespace std;

class SpriteFactory {
 public:
  static AnimatedSprite buildAnimatedSprite(
      string const& animationConfiguration);

  static Sprite buildSprite();
};

#endif /* SpriteFactory_hpp */