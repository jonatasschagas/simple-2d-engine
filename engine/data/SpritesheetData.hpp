#pragma once
#ifndef SPRITESHEETDATA_HPP
#define SPRITESHEETDATA_HPP

#include "SpriteData.hpp"
#include <string>
#include <vector>

using namespace std;

class SpritesheetData {
 public:
  SpritesheetData();
  SpritesheetData(string const& configurationJSONFilename,
                  string const& imageJSONFilename);
  ~SpritesheetData();

  string const& getConfigurationJSONFilename() const;
  string const& getImageFilename() const;
  SpriteData const* getSpriteByName(string const& name) const;

 private:
  vector<SpriteData> m_sprites;
  string m_configurationJSONFilename;
  string m_imageFilename;

  void initializeMembers() {
    m_configurationJSONFilename = "";
    m_imageFilename = "";
    m_sprites.clear();
  }
};

#endif  // SPRITESHEETDATA_HPP
