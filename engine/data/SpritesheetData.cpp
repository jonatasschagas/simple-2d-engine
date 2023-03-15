#include "SpritesheetData.hpp"
#include "../utils/FileUtils.h"
#include <rapidjson/document.h>
#include <string>

using namespace std;
using namespace rapidjson;

SpritesheetData::SpritesheetData() { initializeMembers(); }

SpritesheetData::SpritesheetData(string const& configurationJSON,
                                 string const& imageJSONFilename) {
  initializeMembers();

  m_imageFilename = imageJSONFilename;

  Document configurationDocument;
  configurationDocument.Parse(configurationJSON.c_str());

  auto arraySprites = configurationDocument.GetArray();

  for (SizeType i = 0; i < arraySprites.Size(); i++) {
    auto spriteConfig = arraySprites[i].GetObject();
    string spriteName = spriteConfig["name"].GetString();
    int x = spriteConfig["x"].GetInt();
    int y = spriteConfig["y"].GetInt();
    int width = spriteConfig["width"].GetInt();
    int height = spriteConfig["height"].GetInt();

    SpriteData sprite(spriteName, x, y, width, height);
    m_sprites.push_back(sprite);
  }
}

SpritesheetData::~SpritesheetData() { initializeMembers(); }

SpriteData const* SpritesheetData::getSpriteByName(string const& name) const {
  for (unsigned long i = 0; i < m_sprites.size(); i++) {
    SpriteData const& spriteData = m_sprites.at(i);
    if (spriteData.getName().compare(name) == 0) {
      return &m_sprites.at(i);
    }
  }
  assert(false);  // didn't find the sprite
}

string const& SpritesheetData::getConfigurationJSONFilename() const {
  return m_configurationJSONFilename;
}

string const& SpritesheetData::getImageFilename() const {
  return m_imageFilename;
}
