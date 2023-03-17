#pragma once
#ifndef SDLResourceProvider_hpp
#define SDLResourceProvider_hpp

#include "platform/ResourceProvider.hpp"

class SDLResourceProvider : public ResourceProvider {
 public:
  SDLResourceProvider();
  ~SDLResourceProvider();

  void* loadTexture(string const& path, int* pWidth, int* pHeight) override;

  void readContentsFromFile(string const& path, string* pOutputString) override;
};

#endif /* SDLResourceProvider_hpp */