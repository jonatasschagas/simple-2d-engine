#pragma once
#ifndef OSXResourceProvider_hpp
#define OSXResourceProvider_hpp

#include "disk/ResourceProvider.hpp"

class OSXResourceProvider : public ResourceProvider {
 public:
    void* loadTexture(string const& path, int* pWidth, int* pHeight) override;

  void readContentsFromFile(string const& path, string* pOutputString) override;

  char* readBytesFromFile(string const& path, std::size_t& fileSize) override;

  void writeContentsToFile(string const& path, string const& contents) override;
};

#endif /* OSXResourceProvider_hpp */