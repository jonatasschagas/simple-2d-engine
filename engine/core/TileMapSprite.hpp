#pragma once
#ifndef TileMapSprite_hpp
#define TileMapSprite_hpp

#include "../core/Sprite.hpp"
#include "TileMapMetaTileFactory.hpp"
#include "core/Vector2.h"
#include <stdio.h>
#include <string>

using namespace std;

class TileMapData;
class TileMapLayer;

class TileMapSprite : public Sprite {
 public:
  TileMapSprite();
  TileMapSprite(Vector2 const& tileSizeWorldUnits, TileMapData const* pMapData);
  TileMapSprite(Vector2 const& tileSizeWorldUnits, TileMapData const* pMapData,
                TileMapMetaTileFactory* pTileMapMetaTileFactory,
                string const& metaLayerName);
  ~TileMapSprite();

  void update(float delta) override;

  float const getWorldLimitX() const;

  int getTileX(float x) const;
  int getTileY(float y) const;
  int getTileMapWidth() const;
  int getTileMapHeight() const;

  float getXOffSet() const;
  void setXOffSet(float xOffSet);

  float getYOffSet() const;
  void setYOffSet(float yOffSet);

  int getTileData(int tileX, int tileY, string const& tileLayerName) const;
  int getTileData(float x, float y, string const& tileLayerName) const;

  bool isVisibleInParent(
      GraphicsManager const& rGraphicsManager) const override;

  Vector2 const& getTileSizeInGameUnits() const;
  Vector2 const& getMapSizeInGameUnits() const;

  void setTileMapMetaTileFactory(
      TileMapMetaTileFactory* pTileMapMetaTileFactory);

  void setDisableCamera(bool disableCamera);

 private:
  void loadMap(string const& metaLayerName);

  void loadMapLayers();
  void createTile(int x, int y, Sprite* pSpriteLayer, TileMapLayer* pLayer);
  void createMetaTile(int x, int y, Sprite* pSpriteLayer, TileMapLayer* pLayer);

  TileMapData const* m_pCurrentMapData;
  TileMapLayer* m_pCurrentMapMetaLayer;
  string m_curretMapMetaLayerName;
  Vector2 m_tileSizeInWorldUnits;
  Vector2 m_mapSizeInGameUnits;
  float m_xOffSet;
  float m_yOffSet;
  bool m_disableCamera;

  TileMapMetaTileFactory* m_pTileMapMetaTileFactory;  // optional

  void initializeMembers() {
    m_pCurrentMapMetaLayer = nullptr;
    m_pTileMapMetaTileFactory = nullptr;
    m_tileSizeInWorldUnits.x = 0;
    m_tileSizeInWorldUnits.y = 0;
    m_xOffSet = 0;
    m_yOffSet = 0;
    m_mapSizeInGameUnits.x = 0;
    m_mapSizeInGameUnits.y = 0;
    m_curretMapMetaLayerName = "";
    m_disableCamera = false;
  }
};

#endif /* TileMapSprite_hpp */
