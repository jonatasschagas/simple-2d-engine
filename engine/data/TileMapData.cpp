#include "TileMapData.hpp"
#include <rapidjson/document.h>

using namespace rapidjson;

TileSetConfig::TileSetConfig(string const& name, string const& type,
                             int const columns, int const margin,
                             int const spacing, int const tileCount,
                             int const tileWidth, int const tileHeight,
                             string const& tiledVersion,
                             string const& version) {
  initializeMembers();

  m_name = name;
  m_type = type;
  m_columns = columns;
  m_margin = margin;
  m_spacing = spacing;
  m_tileCount = tileCount;
  m_tileWidth = tileWidth;
  m_tileHeight = tileHeight;
  m_tiledVersion = tiledVersion;
  m_version = version;
}

TileSetConfig::~TileSetConfig() {
  for (int i = 0; i < m_tileConfigs.size(); i++) {
    auto pTileConfig = m_tileConfigs[i];
    delete pTileConfig;
  }

  initializeMembers();
}

string TileSetConfig::getName() const { return m_name; }

string TileSetConfig::getType() const { return m_type; }

int TileSetConfig::getColumns() const { return m_columns; }

int TileSetConfig::getMargin() const { return m_margin; }

int TileSetConfig::getSpacing() const { return m_spacing; }

int TileSetConfig::getTileCount() const { return m_tileCount; }

int TileSetConfig::getTileWidth() const { return m_tileWidth; }

int TileSetConfig::getTileHeight() const { return m_tileHeight; }

string TileSetConfig::getTiledVersion() const { return m_tiledVersion; }

string const& TileSetConfig::getVersion() const { return m_version; }

TileConfig const* TileSetConfig::getTileConfig(int const tileIndex) const {
  return m_tileConfigs[tileIndex];
}

TileConfig* TileSetConfig::addTileConfig(int const id, string const& imageName,
                                         int const x, int const y,
                                         int const width, int const height) {
  TileConfig* pTileConfig = new TileConfig(id, imageName, x, y, width, height);
  m_tileConfigs.push_back(pTileConfig);
  return pTileConfig;
}

TileSet::TileSet(int const firstGid, string const& source,
                 TileSetConfig* pTileSetConfig) {
  initializeMembers();

  m_firstGid = firstGid;
  m_source = source;
  m_pTileSetConfig = pTileSetConfig;
}

TileSet::~TileSet() {
  delete m_pTileSetConfig;

  initializeMembers();
}

int TileSet::getFirstGid() const { return m_firstGid; }

string TileSet::getSource() const { return m_source; }

TileSetConfig* TileSet::getConfig() const { return m_pTileSetConfig; }

TileMapLayer::TileMapLayer(int const id, string const& name, string const& type,
                           vector<int> const& data, int const width,
                           int const height, int const opacity, int const x,
                           int const y, bool const visible) {
  initializeMembers();

  m_id = id;
  m_name = name;
  m_type = type;
  m_data = data;
  m_width = width;
  m_height = height;
  m_opacity = opacity;
  m_x = x;
  m_y = y;
  m_visible = visible;
}

TileMapLayer::~TileMapLayer() { initializeMembers(); }

int TileMapLayer::getId() const { return m_id; }

string TileMapLayer::getName() const { return m_name; }

string TileMapLayer::getType() const { return m_type; }

vector<int> const& TileMapLayer::getData() const { return m_data; }

int TileMapLayer::getWidth() const { return m_width; }

int TileMapLayer::getHeight() const { return m_height; }

int TileMapLayer::getX() const { return m_x; }

int TileMapLayer::getY() const { return m_y; }

int TileMapLayer::getOpacity() const { return m_opacity; }

bool TileMapLayer::isVisible() const { return m_visible; }

bool TileMapLayer::isParallaxLayer() const {
  return m_name.find("hills") != string::npos || m_name.compare("hills") == 0;
}

TileMapData::TileMapData() { initializedMembers(); }

TileMapData::TileMapData(string const& tileMapFilename,
                         string const& locationFolder,
                         string const& tileSetsFolder,
                         ResourceProvider& rResourceProvider) {
  initializedMembers();

  m_tileMapFilename = tileMapFilename;

  string configurationJSON;
  rResourceProvider.readContentsFromFile(m_tileMapFilename, &configurationJSON);

  Document configurationDocument;
  configurationDocument.Parse(configurationJSON.c_str());

  m_height = configurationDocument["height"].GetInt();
  m_width = configurationDocument["width"].GetInt();
  m_infinite = configurationDocument["infinite"].GetBool();
  m_nextLayerId = configurationDocument["nextlayerid"].GetInt();
  m_nextObjectId = configurationDocument["nextobjectid"].GetInt();
  m_tileHeight = configurationDocument["tileheight"].GetInt();
  m_tileWidth = configurationDocument["tilewidth"].GetInt();
  m_version = configurationDocument["version"].GetString();
  m_tileWidth = configurationDocument["tilewidth"].GetInt();
  m_orientation = configurationDocument["orientation"].GetString();
  m_renderOrder = configurationDocument["renderorder"].GetString();
  m_tiledVersion = configurationDocument["tiledversion"].GetString();
  m_type = configurationDocument["type"].GetString();

  auto arrayTileSetsDocument = configurationDocument["tilesets"].GetArray();

  for (int i = 0; i < arrayTileSetsDocument.Size(); i++) {
    auto tileSetDoc = arrayTileSetsDocument[i].GetObject();
    int const firstGid = tileSetDoc["firstgid"].GetInt();
    const string tileSetConfigFile =
        locationFolder + "/" + string(tileSetDoc["source"].GetString());

    string tileSetConfigJSON;
    rResourceProvider.readContentsFromFile(tileSetConfigFile,
                                           &tileSetConfigJSON);
    Document tileSetConfigDocument;
    tileSetConfigDocument.Parse(tileSetConfigJSON.c_str());

    int const columns = tileSetConfigDocument["columns"].GetInt();
    int const margin = tileSetConfigDocument["margin"].GetInt();
    const string name = tileSetConfigDocument["name"].GetString();
    int const spacing = tileSetConfigDocument["spacing"].GetInt();
    int const tileCount = tileSetConfigDocument["tilecount"].GetInt();
    const string tiledVersion =
        tileSetConfigDocument["tiledversion"].GetString();
    int const tileHeight = tileSetConfigDocument["tileheight"].GetInt();
    int const tileWidth = tileSetConfigDocument["tilewidth"].GetInt();
    const string type = tileSetConfigDocument["type"].GetString();
    const string version = tileSetConfigDocument["version"].GetString();

    TileSetConfig* pTileSetConfig =
        new TileSetConfig(name, type, columns, margin, spacing, tileCount,
                          tileWidth, tileHeight, tiledVersion, version);

    if (tileSetConfigDocument.HasMember("image")) {
      const string image = tileSetsFolder + "/" +
                           string(tileSetConfigDocument["image"].GetString());

      for (int j = 0; j < tileCount; j++) {
        int id = j;
        int textureWidth = tileWidth;
        int textureHeight = tileHeight;

        int tileNumberInTileSet = j;

        // extracting the coordinates from the tileset image based on the
        // tileType
        int textureY = (tileNumberInTileSet / columns);
        int textureX = (tileNumberInTileSet - textureY * columns);

        TileConfig* pTileConfig = pTileSetConfig->addTileConfig(
            id, image, textureX * textureWidth, textureY * textureHeight,
            textureWidth, textureHeight);

        if (tileSetConfigDocument.HasMember("tiles")) {
          auto arrayTilesProperties = tileSetConfigDocument["tiles"].GetArray();
          int arrayPropertiesSize = arrayTilesProperties.Size();
          if (arrayPropertiesSize > j) {
            auto tileProperty = arrayTilesProperties[j].GetObject();
            if (tileProperty.HasMember("properties")) {
              auto arrayProperties = tileProperty["properties"].GetArray();
              for (int k = 0; k < arrayProperties.Size(); k++) {
                auto property = arrayProperties[k].GetObject();
                auto name = property["name"].GetString();
                auto value = property["value"].GetString();

                pTileConfig->addProperty(name, value);
              }
            }
          }
        }
      }
    } else if (tileSetConfigDocument.HasMember("tiles")) {
      auto arrayTilesProperties = tileSetConfigDocument["tiles"].GetArray();

      for (int j = 0; j < arrayTilesProperties.Size(); j++) {
        auto tileConfigJson = arrayTilesProperties[j].GetObject();
        int id = tileConfigJson["id"].GetInt();
        string image =
            locationFolder + "/" + string(tileConfigJson["image"].GetString());
        int imageHeight = tileConfigJson["imageheight"].GetInt();
        int imageWidth = tileConfigJson["imagewidth"].GetInt();

        TileConfig* pTileConfig = pTileSetConfig->addTileConfig(
            id, image, 0, 0, imageWidth, imageHeight);

        if (tileConfigJson.HasMember("properties")) {
          auto arrayProperties = tileConfigJson["properties"].GetArray();
          for (int k = 0; k < arrayProperties.Size(); k++) {
            auto property = arrayProperties[k].GetObject();
            auto name = property["name"].GetString();
            auto value = property["value"].GetString();

            pTileConfig->addProperty(name, value);
          }
        }
      }
    }

    TileSet* pTileSet =
        new TileSet(firstGid, tileSetConfigFile, pTileSetConfig);
    m_tileSets.push_back(pTileSet);
  }

  auto arrayLayersDocument = configurationDocument["layers"].GetArray();

  for (int i = 0; i < arrayLayersDocument.Size(); i++) {
    auto layersDoc = arrayLayersDocument[i].GetObject();

    vector<int> dataArray;
    auto dataArrayDoc = layersDoc["data"].GetArray();
    for (int j = 0; j < dataArrayDoc.Size(); j++) {
      dataArray.push_back(dataArrayDoc[j].GetInt());
    }

    int const width = layersDoc["width"].GetInt();
    int const height = layersDoc["height"].GetInt();
    int const x = layersDoc["x"].GetInt();
    int const y = layersDoc["y"].GetInt();
    int const id = layersDoc["id"].GetInt();
    const string name = layersDoc["name"].GetString();
    int const opacity = layersDoc["opacity"].GetInt();
    const string type = layersDoc["type"].GetString();
    bool const visible = layersDoc["visible"].GetBool();

    TileMapLayer* pTileMapLayer = new TileMapLayer(
        id, name, type, dataArray, width, height, opacity, x, y, visible);

    m_layers.push_back(pTileMapLayer);
  }

  // filling the m_tileDataTileSetMap
  for (int i = 0; i < m_layers.size(); i++) {
    TileMapLayer* pMapLayer = m_layers[i];
    vector<int> layerData = pMapLayer->getData();
    for (int j = 0; j < layerData.size(); j++) {
      int tileData = layerData[j];
      if (m_tileDataTileSetMap.count(tileData) == 0) {
        for (int k = 0; k < m_tileSets.size(); k++) {
          TileSet* pTileSet = m_tileSets[k];
          int tileIdLowerBound = pTileSet->getFirstGid();
          int tileIdHigherBound =
              tileIdLowerBound + pTileSet->getConfig()->getTileCount();
          if (tileData >= tileIdLowerBound && tileData < tileIdHigherBound) {
            m_tileDataTileSetMap[tileData] = pTileSet;
            break;
          }
        }
      }
    }
  }
}

TileMapData::~TileMapData() {
  for (int i = 0; i < m_tileSets.size(); i++) {
    TileSet* pTileSet = m_tileSets[i];
    delete pTileSet;
  }

  for (int i = 0; i < m_layers.size(); i++) {
    TileMapLayer* pLayer = m_layers[i];
    delete pLayer;
  }

  initializedMembers();
}

TileSet* TileMapData::getTileSetFromTileData(int const tileData) const {
  if (m_tileDataTileSetMap.count(tileData) == 0) {
    return NULL;
  }
  return m_tileDataTileSetMap.at(tileData);
}

int TileMapData::getWidth() const { return m_width; }

int TileMapData::getHeight() const { return m_height; }

int TileMapData::getTileWidth() const { return m_tileWidth; }

int TileMapData::getTileHeight() const { return m_tileHeight; }

int TileMapData::getNextLayerId() const { return m_nextLayerId; }

int TileMapData::getNextObjectId() const { return m_nextObjectId; }

string const& TileMapData::getVersion() const { return m_version; }

bool TileMapData::isInfinite() const { return m_infinite; }

vector<TileMapLayer*> const& TileMapData::getLayers() const { return m_layers; }

vector<TileSet*> const& TileMapData::getTileSets() const { return m_tileSets; }

string TileMapData::getOrientation() const { return m_orientation; }

string TileMapData::getRenderOrder() const { return m_renderOrder; }

string TileMapData::getTiledVersion() const { return m_tiledVersion; }

string TileMapData::getType() const { return m_type; }
