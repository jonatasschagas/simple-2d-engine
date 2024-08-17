#pragma once
#ifndef OSXResourceProvider_hpp
#define OSXResourceProvider_hpp

#include "disk/ResourceProvider.hpp"

class OSXResourceProvider : public ResourceProvider {
 public:
  void* loadTexture(string const& path, int* pWidth, int* pHeight) override;

  void readContentsFromFile(string const& path, string* pOutputString) override;
};

#endif /* OSXResourceProvider_hpp */