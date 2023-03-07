#pragma once
#ifndef SoundManager_h
#define SoundManager_h

#include <string>

using namespace std;

class SoundManager {
 public:
  /**
   * initialize is called by the Engine when it is first initialized.
   */
  virtual void initialize(){};

  /**
   * playSoundEffect is called by the Engine when a sound effect needs to be
   * played.
   * @param name the name of the sound effect to play
   */
  virtual void playSoundEffect(string const& name) = 0;

  /**
   * playMusic is called by the Engine when music needs to be played.
   * @param path the path to the music to play
   */
  virtual void playMusic(string const& path) = 0;

  /**
   * stopSounds is called by the Engine when all sounds need to be stopped.
   */
  virtual void stopSounds() = 0;

  /**
   * loadMusic is called by the Engine when music needs to be loaded from disk
   * into the sound system.
   * @param path the path to the music to load
   * @return true if the music was loaded successfully, false otherwise
   */
  virtual bool loadMusic(string const& path) = 0;

  /**
   * loadSoundEffect is called by the Engine when a sound effect needs to be
   * loaded from disk into the sound system.
   * @param path the path to the sound effect to load
   * @return true if the sound effect was loaded successfully, false otherwise
   */
  virtual bool loadSoundEffect(string const& name, string const& path) = 0;

  virtual ~SoundManager() {}
};

#endif /* SoundManager_h */