#pragma once
#ifndef SDLSoundManager_hpp
#define SDLSoundManager_hpp

#include "SDL_mixer.h"
#include "sound/SoundManager.hpp"
#include <map>
#include <stdio.h>
#include <string>
#include <vector>

class SDLSoundManager : public SoundManager {
 public:
  SDLSoundManager();
  ~SDLSoundManager();

  void playSoundEffect(std::string const& name) override;

  void playMusic(std::string const& path) override;

  void stopSounds() override;

  bool loadMusic(std::string const& path) override;

  bool loadSoundEffect(std::string const& name,
                       std::string const& path) override;

 private:
  std::map<std::string, Mix_Chunk*> m_soundEffects;
  std::map<std::string, Mix_Music*> m_songs;
  bool m_sounds;

  void initializeMembers() {
    m_soundEffects.clear();
    m_songs.clear();
    m_sounds = true;
  }
};

#endif /* SDLSoundManager_hpp */