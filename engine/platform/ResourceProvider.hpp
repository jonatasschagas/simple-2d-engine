#pragma once
#ifndef ResourceProvider_hpp
#define ResourceProvider_hpp

#include <string>

using namespace std;

class ResourceProvider {
 public:
  virtual void* loadTexture(string const& path, int* pWidth, int* pHeight) = 0;

  virtual void readContentsFromFile(string const& path,
                                    string* pOutputString) = 0;
};

#endif /* ResourceProvider_hpp */