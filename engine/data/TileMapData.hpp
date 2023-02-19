#pragma once
#ifndef TileMapData_hpp
#define TileMapData_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <map>

using namespace std;

class TileConfig
{
public:
    
    TileConfig(const int id,
               const string& imageName,
               const int x,
               const int y,
               const int width,
               const int height)
    {
        initializeMembers();
        
        m_id = id;
        m_imageName = imageName;
        m_x = x;
        m_y = y;
        m_width = width;
        m_height = height;
    }
    
    const int getTileId() const { return m_id; }
    const string& getImageName() const { return m_imageName; }
    const int getX() const { return m_x; }
    const int getY() const { return m_y; }
    const int getWidth() const { return m_width; }
    const int getHeight() const { return m_height; }
    
    void addProperty(const string& key, const string& value)
    {
        m_properties[key] = value;
    }

    const string getProperty(const string& key) const
    {
        map<string, string>::const_iterator it = m_properties.find(key);
        if (it != m_properties.end())
        {
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
    
    void initializeMembers()
    {
        m_x = 0;
        m_y = 0;
        m_width = 0;
        m_height = 0;
        m_imageName = "";
        m_properties.clear();
    }
    
};

class TileSetConfig
{
public:
    
    TileSetConfig(const string& name,
                  const string& type,
                  const int columns,
                  const int margin,
                  const int spacing,
                  const int tileCount,
                  const int tileWidth,
                  const int tileHeight,
                  const string& tiledVersion,
                  const string& version);
    
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
    const TileConfig* getTileConfig(const int tileIndex) const;
    TileConfig* addTileConfig(const int id, 
                              const string& imageName, 
                              const int x, 
                              const int y, 
                              const int width, 
                              const int height);
    const string& getVersion() const;
    
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
    
    void initializeMembers()
    {
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

class TileSet
{
public:
    
    TileSet(const int firstGid, 
            const string& source, 
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
    
    void initializeMembers()
    {
        m_firstGid = -1;
        m_source = "";
        m_pTileSetConfig = NULL;
    }
};

class TileMapLayer
{
public:
    
    TileMapLayer(const int id, 
                 const string& name, 
                 const string& type, 
                 const vector<int>& data, 
                 const int width, 
                 const int height, 
                 const int opacity, 
                 const int x, 
                 const int y, 
                 const bool visible);
    ~TileMapLayer();
    
    int getId() const;
    string getName() const;
    string getType() const;
    const vector<int>& getData() const;
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
    
    void initializeMembers()
    {
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

class TileMapData
{
public:
    
    TileMapData(const string& tileMapFilename, 
                const string& levelsFolder, 
                const string& tileSetsFolder);
    ~TileMapData();
    
    int getWidth() const;
    int getHeight() const;
    int getTileWidth() const;
    int getTileHeight() const;
    int getNextLayerId() const;
    int getNextObjectId() const;
    
    const string& getVersion() const;
    
    bool isInfinite() const;
    
    const vector<TileMapLayer*>& getLayers() const;
    const vector<TileSet*>& getTileSets() const;
    
    string getOrientation() const;
    string getRenderOrder() const;
    string getTiledVersion() const;
    string getType() const;
    
    TileSet* getTileSetFromTileData(const int tileData) const;
    
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
    map<int,TileSet*> m_tileDataTileSetMap;
    
    string m_orientation;
    string m_renderOrder;
    string m_tiledVersion;
    string m_type;
    
    void initializedMembers()
    {
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
