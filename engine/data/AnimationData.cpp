#include "AnimationData.hpp"

AnimationData::AnimationData(const string& name, ConstJSONObject* pJsonObject)
{
    m_timePerSprite = pJsonObject->FindMember("timePerSprite")->value.GetFloat();
    auto arraySprites = pJsonObject->FindMember("sprites")->value.GetArray();
    m_playOnce = pJsonObject->FindMember("playOnce")->value.GetBool();
    m_name = name;
    
    for (SizeType i = 0; i < arraySprites.Size(); i++)
    {
        string animationName = arraySprites[i].GetString();
        m_sprites.push_back(animationName);
    }
    
    if (pJsonObject->HasMember("leftOffsetX"))
    {
        m_leftOffset.x = pJsonObject->FindMember("leftOffsetX")->value.GetFloat();
        m_leftOffset.y = pJsonObject->FindMember("leftOffsetY")->value.GetFloat();
    }
    
    if (pJsonObject->HasMember("rightOffsetX"))
    {
        m_rightOffset.x = pJsonObject->FindMember("rightOffsetX")->value.GetFloat();
        m_rightOffset.y = pJsonObject->FindMember("rightOffsetY")->value.GetFloat();
    }
    
    if (pJsonObject->HasMember("offsetX"))
    {
        m_leftOffset.x = pJsonObject->FindMember("offsetX")->value.GetFloat();
        m_rightOffset.x = pJsonObject->FindMember("offsetX")->value.GetFloat();
    }
    
    if (pJsonObject->HasMember("offsetY"))
    {
        m_leftOffset.y = pJsonObject->FindMember("offsetY")->value.GetFloat();
        m_rightOffset.y = pJsonObject->FindMember("offsetY")->value.GetFloat();
    }
    
    if (pJsonObject->HasMember("soundEffect"))
    {
        m_soundEffect = pJsonObject->FindMember("soundEffect")->value.GetString();
    }
    
    if (pJsonObject->HasMember("advanceAnimationManually"))
    {
        m_advanceAnimationManually = pJsonObject->FindMember("advanceAnimationManually")->value.GetBool();
    }
}

AnimationData::AnimationData(const string& name, JSONObject* pJsonObject)
{
    m_timePerSprite = pJsonObject->FindMember("timePerSprite")->value.GetFloat();
    auto arraySprites = pJsonObject->FindMember("sprites")->value.GetArray();
    m_playOnce = pJsonObject->FindMember("playOnce")->value.GetBool();
    m_name = name;
    
    for (SizeType i = 0; i < arraySprites.Size(); i++)
    {
        string animationName = arraySprites[i].GetString();
        m_sprites.push_back(animationName);
    }
    
    if (pJsonObject->HasMember("leftOffsetX"))
    {
        m_leftOffset.x = pJsonObject->FindMember("leftOffsetX")->value.GetFloat();
        m_leftOffset.y = pJsonObject->FindMember("leftOffsetY")->value.GetFloat();
    }
    
    if (pJsonObject->HasMember("rightOffsetX"))
    {
        m_rightOffset.x = pJsonObject->FindMember("rightOffsetX")->value.GetFloat();
        m_rightOffset.y = pJsonObject->FindMember("rightOffsetY")->value.GetFloat();
    }
    
    if (pJsonObject->HasMember("offsetX"))
    {
        m_leftOffset.x = pJsonObject->FindMember("offsetX")->value.GetFloat();
        m_rightOffset.x = pJsonObject->FindMember("offsetX")->value.GetFloat();
    }
    
    if (pJsonObject->HasMember("offsetY"))
    {
        m_leftOffset.y = pJsonObject->FindMember("offsetY")->value.GetFloat();
        m_rightOffset.y = pJsonObject->FindMember("offsetY")->value.GetFloat();
    }
    
    if (pJsonObject->HasMember("soundEffect"))
    {
        m_soundEffect = pJsonObject->FindMember("soundEffect")->value.GetString();
    }
    
    if (pJsonObject->HasMember("advanceAnimationManually"))
    {
        m_advanceAnimationManually = pJsonObject->FindMember("advanceAnimationManually")->value.GetBool();
    }
}

AnimationData::~AnimationData()
{}

string AnimationData::loadNextSprite()
{
    string currentSprite = m_sprites[m_currentSpriteIndex];
    if (m_currentSpriteIndex + 1 >= m_sprites.size())
    {
        if (m_playOnce)
        {
            return currentSprite;
        }
        m_currentSpriteIndex = 0;
    }
    else
    {
        m_currentSpriteIndex++;
    }
    return currentSprite;
}
