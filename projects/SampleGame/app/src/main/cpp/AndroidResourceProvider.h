#ifndef ANDROID_RESOURCE_PROVIDER_H
#define ANDROID_RESOURCE_PROVIDER_H

#include "platform/ResourceProvider.hpp"
#include <GLES3/gl3.h>
#include <android/asset_manager.h>
#include <memory>
#include <string>
#include <vector>

using std::string;

class AndroidResourceProvider : public ResourceProvider {
 public:
  AndroidResourceProvider(AAssetManager* pAssetManager);

  void* loadTexture(string const& path, int* pWidth, int* pHeight) override;

  void readContentsFromFile(string const& path, string* pOutputString) override;

  ~AndroidResourceProvider();

 private:
  AAssetManager* m_pAssetManager;

  void initializeMembers() { m_pAssetManager = nullptr; }
};

#endif  // ANDROID_RESOURCE_PROVIDER_H