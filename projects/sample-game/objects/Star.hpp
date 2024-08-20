#pragma once

#ifndef Star_hpp
#define Star_hpp

#include "core/ColoredSprite.hpp"
#include <string>
#include <vector>

class Star : public ColoredSprite {
 public:
  Star(glm::vec4 color);
  ~Star() {}

  void update(float delta) override;

 private:
  void renderSprite(GraphicsManager& rGraphicsManager) override;
};

#endif /* Star_hpp */