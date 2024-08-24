#pragma once
#ifndef ResourceProvider_hpp
#define ResourceProvider_hpp

#include <string>

using std::string;

class ResourceProvider {
 public:
  virtual void* loadTexture(string const& path, int* pWidth, int* pHeight) = 0;

  virtual void readContentsFromFile(string const& path,
                                    string* pOutputString) = 0;

  virtual char* readBytesFromFile(string const& path,
                                  std::size_t& fileSize) = 0;

  virtual void writeContentsToFile(string const& path,
                                   string const& contents) = 0;
};

#endif /* ResourceProvider_hpp */