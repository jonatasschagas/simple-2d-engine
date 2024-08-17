#pragma once
#ifndef MuteSoundManager_hpp
#define MuteSoundManager_hpp

#include "sound/SoundManager.hpp"

class MuteSoundManager : public SoundManager {
 public:
  void initialize() override {}

  void playSoundEffect(string const& name) override {}

  void playMusic(string const& path) override {}

  void stopSounds() override {}

  bool loadMusic(string const& path) override { return true; }

  bool loadSoundEffect(string const& name, string const& path) override {
    return true;
  }

  ~MuteSoundManager() {}
};

#endif /* MuteSoundManager_hpp */