#pragma once
#ifndef SDLSoundManager_hpp
#define SDLSoundManager_hpp

#include "SDL_mixer.h"
#include "platform/SoundManager.hpp"
#include <map>
#include <stdio.h>
#include <string>
#include <vector>

using std::map;
using std::string;
using std::vector;

class SDLSoundManager : public SoundManager {
 public:
  SDLSoundManager();
  ~SDLSoundManager();

  void playSoundEffect(string const& name) override;

  void playMusic(string const& path) override;

  void stopSounds() override;

  bool loadMusic(string const& path) override;

  bool loadSoundEffect(string const& name, string const& path) override;

 private:
  map<string, Mix_Chunk*> m_soundEffects;
  map<string, Mix_Music*> m_songs;
  bool m_sounds;

  void initializeMembers() {
    m_soundEffects.clear();
    m_songs.clear();
    m_sounds = true;
  }
};

#endif /* SDLSoundManager_hpp */