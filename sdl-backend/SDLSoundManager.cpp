#include "SDLSoundManager.hpp"

SDLSoundManager::SDLSoundManager() { initializeMembers(); }

SDLSoundManager::~SDLSoundManager() {
  for (auto it = m_songs.begin(); it != m_songs.end(); ++it) {
    string path = it->first;
    auto pMUS = it->second;
    Mix_FreeMusic(pMUS);
    pMUS = nullptr;
  }

  for (auto it = m_soundEffects.begin(); it != m_soundEffects.end(); ++it) {
    string path = it->first;
    auto pSEffc = it->second;
    Mix_FreeChunk(pSEffc);
    pSEffc = nullptr;
  }
  initializeMembers();
}

void SDLSoundManager::playSoundEffect(string const& name) {
  if (!m_sounds) {
    return;
  }

  map<string, Mix_Chunk*>::iterator it = m_soundEffects.find(name);
  if (it == m_soundEffects.end()) {
    // not found
    return;
  }

  Mix_Chunk* pSoundEffect = m_soundEffects.at(name);
  Mix_PlayChannel(-1, pSoundEffect, 0);
}

void SDLSoundManager::playMusic(string const& path) {
  if (!m_sounds) {
    return;
  }

  map<string, Mix_Music*>::iterator it = m_songs.find(path);
  if (it == m_songs.end()) {
    // element not found;
    return;
  }

  Mix_Music* pMusic = m_songs.at(path);
  Mix_PlayMusic(pMusic, -1);
  Mix_VolumeMusic(25);
}

void SDLSoundManager::stopSounds() {
  Mix_PauseMusic();
  m_sounds = false;
}

bool SDLSoundManager::loadMusic(string const& path) {
  map<string, Mix_Music*>::iterator it = m_songs.find(path);
  if (it != m_songs.end()) {
    // already loaded;
    return true;
  }

  bool success = true;
  Mix_Music* pMusic = Mix_LoadMUS(path.c_str());
  if (pMusic == NULL) {
    printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
    success = false;
  } else {
    m_songs[path] = pMusic;
  }

  return success;
}

bool SDLSoundManager::loadSoundEffect(string const& name, string const& path) {
  map<string, Mix_Chunk*>::iterator it = m_soundEffects.find(name);
  if (it != m_soundEffects.end()) {
    // already loaded;
    return true;
  }

  bool success = true;
  Mix_Chunk* pSound = Mix_LoadWAV(path.c_str());
  if (pSound == NULL) {
    printf("Failed to load sound effect! SDL_mixer Error: %s\n",
           Mix_GetError());
    success = false;
  } else {
    m_soundEffects[name] = pSound;
  }

  return success;
}
