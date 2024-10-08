#include "AndroidResourceProvider.h"
#include "AndroidOut.h"
#include <android/imagedecoder.h>
#include <cassert>
#include <string>

AndroidResourceProvider::AndroidResourceProvider(AAssetManager* pAssetManager) {
  initializeMembers();
  m_pAssetManager = pAssetManager;
}

void* AndroidResourceProvider::loadTexture(string const& path, int* pWidth,
                                           int* pHeight) {
  AAsset* pAsset =
      AAssetManager_open(m_pAssetManager, path.c_str(), AASSET_MODE_STREAMING);
  AImageDecoder* decoder;
  int result = AImageDecoder_createFromAAsset(pAsset, &decoder);
  assert(result == ANDROID_IMAGE_DECODER_SUCCESS);

  AImageDecoderHeaderInfo const* info = AImageDecoder_getHeaderInfo(decoder);
  int32_t width = AImageDecoderHeaderInfo_getWidth(info);
  int32_t height = AImageDecoderHeaderInfo_getHeight(info);
  AndroidBitmapFormat format =
      (AndroidBitmapFormat)AImageDecoderHeaderInfo_getAndroidBitmapFormat(info);
  size_t stride =
      AImageDecoder_getMinimumStride(decoder);  // Image decoder does not
  // use padding by default
  size_t size = height * stride;
  void* pPixels = malloc(size);

  result = AImageDecoder_decodeImage(decoder, pPixels, stride, size);
  assert(result == ANDROID_IMAGE_DECODER_SUCCESS);

  // We’re done with the decoder, so now it’s safe to delete it.
  AImageDecoder_delete(decoder);

  // The decoder is no longer accessing the AAsset, so it is safe to
  // close it.
  AAsset_close(pAsset);

  *pWidth = width;
  *pHeight = height;

  return pPixels;
}

void AndroidResourceProvider::readContentsFromFile(string const& path,
                                                   string* pOutputString) {
  if (path.empty()) return;

  auto pFile =
      AAssetManager_open(m_pAssetManager, path.c_str(), AASSET_MODE_UNKNOWN);
  auto size = AAsset_getLength(pFile);
  std::string buffer(size, ' ');
  AAsset_read(pFile, const_cast<char*>(buffer.c_str()), size);
  *pOutputString = buffer;
  AAsset_close(pFile);
}

char* AndroidResourceProvider::readBytesFromFile(string const& path,
                                                 std::size_t& fileSize) {
  AAsset* asset =
      AAssetManager_open(m_pAssetManager, path.c_str(), AASSET_MODE_BUFFER);

  assert(asset && "Asset not found.");

  fileSize = AAsset_getLength(asset);

  char* buffer = new char[fileSize];
  AAsset_read(asset, buffer, fileSize);

  AAsset_close(asset);

  return buffer;
}

void AndroidResourceProvider::writeContentsToFile(string const& path,
                                                  string const& contents) {
  // TODO: Implement this
}

AndroidResourceProvider::~AndroidResourceProvider() { initializeMembers(); }