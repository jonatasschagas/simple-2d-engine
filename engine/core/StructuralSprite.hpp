#pragma once
#ifndef StructuralSprite_hpp
#define StructuralSprite_hpp

#include "Sprite.hpp"

/**
 * StructuralSprite is a class that represents a sprite with no rendering.
 * @ingroup graphics
 */
class StructuralSprite : public Sprite {
 public:
 private:
  void renderSprite(GraphicsManager& rGraphicsManager) override {};
};

#endif /* StructuralSprite_hpp */