//
// Created by Jonatas Chagas on 1.11.2023.
//
#pragma once
#ifndef ANDROIDSOUNDMANAGER_H
#define ANDROIDSOUNDMANAGER_H

#include "AudioFile.h"
#include "disk/ResourceProvider.hpp"
#include "sound/SoundManager.hpp"
#include <oboe/Oboe.h>
#include <map>
#include <string>

static const float VOLUME = 1.0f;
using std::map;
using std::string;

struct CurrentSound {
  AudioFile<int16_t>* pAudio = nullptr;
  int sampleIndex = 0;
  bool loop = false;
  float volume = 1.0f;
  CurrentSound* pPrevious = nullptr;
  CurrentSound* pNext = nullptr;
};

class AndroidSoundManager : public SoundManager,
                            public oboe::AudioStreamDataCallback {
 public:
  static constexpr auto channelCount = oboe::ChannelCount::Stereo;

  AndroidSoundManager(ResourceProvider* pResourceProvider, int samplingRate);
  ~AndroidSoundManager();

  virtual void initialize() override;

  virtual void playSoundEffect(string const& name) override;

  virtual void playMusic(string const& name) override;

  virtual void stopSounds() override;

  virtual bool loadMusic(string const& path) override;

  virtual bool loadSoundEffect(string const& name, string const& path) override;

  oboe::DataCallbackResult onAudioReady(oboe::AudioStream* audioStream,
                                        void* audioData,
                                        int32_t framesCount) override;

 private:
  bool loadAudioFile(string const& name, string const& path);

  void openStream(int samplingRate);

  void appendSound(AudioFile<int16_t>* pAudio, bool loop, float volume);
  void removeSound(AudioFile<int16_t>* pAudio);

  int m_samplingRate;
  oboe::AudioStream* m_pStream;
  map<string, AudioFile<int16_t>*> m_audioMap;
  ResourceProvider* m_pResourceProvider;

  CurrentSound* m_pCurrentSound;

  void initializeMembers() {
    m_samplingRate = 0;
    m_pStream = nullptr;
    m_pResourceProvider = nullptr;
    m_audioMap.clear();
    m_pCurrentSound = nullptr;
  }
};

#endif  // ANDROIDSOUNDMANAGER_H
