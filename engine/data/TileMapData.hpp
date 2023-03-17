#pragma once
#ifndef TileMapData_hpp
#define TileMapData_hpp

#include "platform/ResourceProvider.hpp"
#include <map>
#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

class TileConfig {
 public:
  TileConfig(int const id, string const& imageName, int const x, int const y,
             int const width, int const height) {
    initializeMembers();

    m_id = id;
    m_imageName = imageName;
    m_x = x;
    m_y = y;
    m_width = width;
    m_height = height;
  }

  int const getTileId() const { return m_id; }
  string const& getImageName() const { return m_imageName; }
  int const getX() const { return m_x; }
  int const getY() const { return m_y; }
  int const getWidth() const { return m_width; }
  int const getHeight() const { return m_height; }

  void addProperty(string const& key, string const& value) {
    m_properties[key] = value;
  }

  const string getProperty(string const& key) const {
    map<string, string>::const_iterator it = m_properties.find(key);
    if (it != m_properties.end()) {
      return it->second;
    }

    return "";
  }

 private:
  int m_id;
  string m_imageName;
  int m_x;
  int m_y;
  int m_width;
  int m_height;
  map<string, string> m_properties;

  void initializeMembers() {
    m_x = 0;
    m_y = 0;
    m_width = 0;
    m_height = 0;
    m_imageName = "";
    m_properties.clear();
  }
};

class TileSetConfig {
 public:
  TileSetConfig(string const& name, string const& type, int const columns,
                int const margin, int const spacing, int const tileCount,
                int const tileWidth, int const tileHeight,
                string const& tiledVersion, string const& version);

  ~TileSetConfig();

  string getName() const;
  string getType() const;
  int getColumns() const;
  int getMargin() const;
  int getSpacing() const;
  int getTileCount() const;
  int getTileWidth() const;
  int getTileHeight() const;
  string getTiledVersion() const;
  TileConfig const* getTileConfig(int const tileIndex) const;
  TileConfig* addTileConfig(int const id, string const& imageName, int const x,
                            int const y, int const width, int const height);
  string const& getVersion() const;

 private:
  string m_name;
  string m_type;
  string m_image;
  int m_imageWidth;
  int m_imageHeight;
  int m_columns;
  int m_margin;
  int m_spacing;
  int m_tileCount;
  int m_tileWidth;
  int m_tileHeight;
  string m_tiledVersion;
  vector<TileConfig*> m_tileConfigs;
  string m_version;

  void initializeMembers() {
    m_name = "";
    m_type = "";
    m_image = "";
    m_tileConfigs.clear();
    m_imageWidth = 0;
    m_imageHeight = 0;
    m_columns = 0;
    m_margin = 0;
    m_spacing = 0;
    m_tileCount = 0;
    m_tileWidth = 0;
    m_tileHeight = 0;
    m_tiledVersion = "";
    m_version = "";
  }
};

class TileSet {
 public:
  TileSet(int const firstGid, string const& source,
          TileSetConfig* pTileSetConfig);
  ~TileSet();

  int getFirstGid() const;
  string getSource() const;
  TileSetConfig* getConfig() const;

  int m_spriteId;

 private:
  int m_firstGid;
  string m_source;
  TileSetConfig* m_pTileSetConfig;

  void initializeMembers() {
    m_firstGid = -1;
    m_source = "";
    m_pTileSetConfig = NULL;
  }
};

class TileMapLayer {
 public:
  TileMapLayer(int const id, string const& name, string const& type,
               vector<int> const& data, int const width, int const height,
               int const opacity, int const x, int const y, bool const visible);
  ~TileMapLayer();

  int getId() const;
  string getName() const;
  string getType() const;
  vector<int> const& getData() const;
  int getWidth() const;
  int getHeight() const;
  int getX() const;
  int getY() const;
  int getOpacity() const;
  bool isVisible() const;
  bool isParallaxLayer() const;

 private:
  int m_id;
  string m_name;
  string m_type;
  vector<int> m_data;
  int m_width;
  int m_height;
  int m_opacity;
  int m_x;
  int m_y;
  bool m_visible;

  void initializeMembers() {
    m_id = -1;
    m_name = "";
    m_type = "";
    m_data.clear();
    m_width = -1;
    m_height = -1;
    m_opacity = -1;
    m_x = -1;
    m_y = -1;
    m_visible = false;
  }
};

class TileMapData {
 public:
  TileMapData();
  TileMapData(string const& tileMapFilename, string const& levelsFolder,
              string const& tileSetsFolder,
              ResourceProvider& rResourceProvider);
  ~TileMapData();

  int getWidth() const;
  int getHeight() const;
  int getTileWidth() const;
  int getTileHeight() const;
  int getNextLayerId() const;
  int getNextObjectId() const;

  string const& getVersion() const;

  bool isInfinite() const;

  vector<TileMapLayer*> const& getLayers() const;
  vector<TileSet*> const& getTileSets() const;

  string getOrientation() const;
  string getRenderOrder() const;
  string getTiledVersion() const;
  string getType() const;

  TileSet* getTileSetFromTileData(int const tileData) const;

 private:
  string m_tileMapFilename;

  int m_width;
  int m_height;
  int m_tileWidth;
  int m_tileHeight;
  int m_nextLayerId;
  int m_nextObjectId;

  string m_version;
  bool m_infinite;

  vector<TileMapLayer*> m_layers;
  vector<TileSet*> m_tileSets;
  map<int, TileSet*> m_tileDataTileSetMap;

  string m_orientation;
  string m_renderOrder;
  string m_tiledVersion;
  string m_type;

  void initializedMembers() {
    m_tileMapFilename = "";
    m_width = 0;
    m_height = 0;
    m_tileWidth = 0;
    m_tileHeight = 0;
    m_nextLayerId = 0;
    m_nextObjectId = 0;

    m_version = "";
    m_infinite = false;

    m_layers.clear();
    m_tileSets.clear();
    m_tileDataTileSetMap.clear();

    m_orientation = "";
    m_renderOrder = "";
    m_tiledVersion = "";
    m_type = "";
  }
};

#endif /* TileMapData_hpp */
