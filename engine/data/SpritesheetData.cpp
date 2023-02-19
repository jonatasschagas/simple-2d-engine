#include "SpritesheetData.hpp"
#include "../utils/FileUtils.h"

#include <rapidjson/document.h>
#include <string>

using namespace std;
using namespace rapidjson;

SpritesheetData::SpritesheetData(const string& configurationJSONFilename, const string& imageJSONFilename)
{
    initializeMembers();

    m_configurationJSONFilename = configurationJSONFilename;
    m_imageFilename = imageJSONFilename;
    
    string configurationJSON = loadFile(configurationJSONFilename);

    Document configurationDocument;
    configurationDocument.Parse(configurationJSON.c_str());

    auto arraySprites = configurationDocument.GetArray();
    m_pSprites = new vector<SpriteData*>();
    
    for (SizeType i = 0; i < arraySprites.Size(); i++)
    {
        auto spriteConfig = arraySprites[i].GetObject();
        string spriteName = spriteConfig["name"].GetString();
        int x = spriteConfig["x"].GetInt();
        int y = spriteConfig["y"].GetInt();
        int width = spriteConfig["width"].GetInt();
        int height = spriteConfig["height"].GetInt();
        
        SpriteData* pSprite = new SpriteData(spriteName, x, y, width, height);
        m_pSprites->push_back(pSprite);
    }

}

SpritesheetData::~SpritesheetData()
{
    if (m_pSprites)
    {
        for (int i = 0; i < m_pSprites->size(); i++)
        {
            SpriteData* pSprite = m_pSprites->at(i);
            delete pSprite;
        }
        delete m_pSprites;
    }

    initializeMembers();
}

SpriteData* SpritesheetData::getSpriteByName(const string& name) const
{
    // find sprite
    if (m_pSprites)
    {
        for (int i = 0; i < m_pSprites->size(); i++)
        {
            SpriteData* pSpriteData = m_pSprites->at(i);
            if (pSpriteData && pSpriteData->getName().compare(name) == 0)
            {
                return pSpriteData;
            }
        }
    }
    
    return NULL;
}

const string& SpritesheetData::getConfigurationJSONFilename() const
{
    return m_configurationJSONFilename;
}

const string& SpritesheetData::getImageFilename() const
{
    return m_imageFilename;
}
