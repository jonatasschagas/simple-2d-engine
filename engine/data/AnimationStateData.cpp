#include "AnimationStateData.hpp"

AnimationStateData::AnimationStateData(JSONObject* pJSON)
{
    initializeMembers();
    
    m_name = pJSON->FindMember("name")->value.GetString();
    m_playOnce = pJSON->FindMember("playOnce")->value.GetBool();
    m_timePerSprite = pJSON->FindMember("timePerSprite")->value.GetFloat();
    
    if (pJSON->HasMember("soundEffect"))
        m_soundEffect = pJSON->FindMember("soundEffect")->value.GetString();
    
    if (pJSON->HasMember("advanceAnimationManually"))
        m_advanceAnimationManually = pJSON->FindMember("advanceAnimationManually")->value.GetBool();
    
    if (pJSON->HasMember("offsetX"))
        m_offsetX = pJSON->FindMember("offsetX")->value.GetFloat();
    
    if (pJSON->HasMember("offsetY"))
        m_offsetY = pJSON->FindMember("offsetY")->value.GetFloat();
    
    auto pSpritesArray = pJSON->FindMember("sprites")->value.GetArray();
    
    for (int i = 0; i < pSpritesArray.Size(); i++)
    {
        m_spriteNames.push_back(pSpritesArray[i].GetString());
    }
}
