#pragma once
#ifndef SPRITESHEETDATA_HPP
#define SPRITESHEETDATA_HPP

#include "SpriteData.hpp"
#include <string>
#include <vector>

using namespace std;

class SpritesheetData
{
public:

    SpritesheetData(const string& configurationJSONFilename, const string& imageJSONFilename);
    ~SpritesheetData();

    const string& getConfigurationJSONFilename() const;
    const string& getImageFilename() const;
    SpriteData* getSpriteByName(const string& name) const;
    
private:

    vector<SpriteData*>* m_pSprites;
    string m_configurationJSONFilename;
    string m_imageFilename;

    void initializeMembers()
    {
        m_pSprites = NULL;
        m_configurationJSONFilename = "";
        m_imageFilename = "";
    }

};


#endif //SPRITESHEETDATA_HPP
