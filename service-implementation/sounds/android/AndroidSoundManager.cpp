//
// Created by Jonatas Chagas on 1.11.2023.
//

#include "AndroidSoundManager.hpp"
#include "AudioFile.h"
#include "utils/Logging.h"
#include "utils/MathUtils.h"
#include <string>

using namespace oboe;

AndroidSoundManager::AndroidSoundManager(ResourceProvider* pResourceProvider,
                                         int samplingRate)
    : m_samplingRate(samplingRate), m_pResourceProvider(pResourceProvider) {}

AndroidSoundManager::~AndroidSoundManager() {
  m_pStream->close();
  delete m_pStream;

  for (auto& entry : m_audioMap) {
    delete entry.second;
  }
  m_audioMap.clear();

  initializeMembers();
}

void AndroidSoundManager::initialize() {
  m_pStream = nullptr;
  openStream(m_samplingRate);
}

void AndroidSoundManager::openStream(int samplingRate) {
  if (m_pStream != nullptr) {
    m_pStream->close();
  }

  // Create an AudioStream using the Oboe's builder
  AudioStreamBuilder builder;
  auto const result =
      builder.setPerformanceMode(PerformanceMode::None)
          ->setDirection(Direction::Output)
          ->setSampleRate(samplingRate)
          ->setDataCallback(this)
          ->setSharingMode(SharingMode::Exclusive)
          ->setFormat(AudioFormat::I16)
          ->setChannelCount(channelCount)
          ->setUsage(oboe::Usage::Game)
          ->setFramesPerDataCallback(10000)
          ->setSampleRateConversionQuality(SampleRateConversionQuality::Low)
          ->openStream(&m_pStream);

  if (result != Result::OK) {
    // indicate that stream creation has failed
    string errorMessage = "Error initializing Oboe sound system. " +
                          std::to_string(static_cast<int>(result));
    logMessage(LogLevel::Error, "AndroidSoundManager", errorMessage.c_str());
    std::abort();
  }

  string infoMessage = "Oboe sound system has been initialized. Sample Rate: " +
                       std::to_string(static_cast<int>(m_samplingRate));
  logMessage(LogLevel::Info, "AndroidSoundManager", infoMessage.c_str());
}

void AndroidSoundManager::playSoundEffect(string const& name) {
  if (m_audioMap.find(name) == m_audioMap.end()) {
    logMessage(LogLevel::Error, "AndroidSoundManager",
               ("Error reading the sound effect " + name).c_str());
    return;
  }

  AudioFile<int16_t>* pAudio = m_audioMap[name];
  appendSound(pAudio, false, VOLUME);
  m_pStream->requestStart();
}

void AndroidSoundManager::playMusic(string const& name) {
  if (m_audioMap.find(name) == m_audioMap.end()) {
    logMessage(LogLevel::Error, "AndroidSoundManager",
               ("Error reading the song " + name).c_str());
    return;
  }
  AudioFile<int16_t>* pAudio = m_audioMap[name];
  appendSound(pAudio, true, VOLUME);
  m_pStream->requestStart();
}

void AndroidSoundManager::stopSounds() { m_pStream->requestStop(); }

bool AndroidSoundManager::loadAudioFile(string const& name,
                                        string const& path) {
  if (m_audioMap.find(name) != m_audioMap.end()) {
    logMessage(LogLevel::Warning, "AndroidSoundManager",
               "Audio File " + name + " has already been loaded.");
    return true;
  }

  auto pAudioFile = new AudioFile<int16_t>();

  std::size_t fileSize = 0;
  char* pAudioData = m_pResourceProvider->readBytesFromFile(path, fileSize);
  std::vector<uint8_t> fileData;

  // Check if the read was successful
  if (pAudioData && fileSize > 0) {
    // Copy pAudioData to fileData
    fileData.assign(pAudioData, pAudioData + fileSize);

    // Assuming pAudioFile is an object that can load from memory
    // (e.g., a library-specific audio file loader)
    pAudioFile->loadFromMemory(fileData);

    delete[] pAudioData;

    logMessage(
        LogLevel::Info, "AndroidSoundManager",
        "-------------------------------------------------------------------");
    logMessage(LogLevel::Info, "AndroidSoundManager",
               "Read audio file: " + path);
    logMessage(LogLevel::Info, "AndroidSoundManager",
               "Num Channels: " + std::to_string(pAudioFile->getNumChannels()));
    logMessage(LogLevel::Info, "AndroidSoundManager",
               "Num Samples Per Channel: " +
                       std::to_string(pAudioFile->getNumSamplesPerChannel()));
    logMessage(LogLevel::Info, "AndroidSoundManager",
               "Sample Rate: " + std::to_string(pAudioFile->getSampleRate()));
    logMessage(LogLevel::Info, "AndroidSoundManager",
               "Bit Depth: " + std::to_string(pAudioFile->getBitDepth()));
    logMessage(
        LogLevel::Info, "AndroidSoundManager",
        "Length in Seconds: " + std::to_string(pAudioFile->getLengthInSeconds()));
    logMessage(
        LogLevel::Info, "AndroidSoundManager",
        "-------------------------------------------------------------------");

  } else {
    logMessage(LogLevel::Error, "AndroidSoundManager",
               "Failed to read audio file: " + path);
    std::abort();
  }

  m_audioMap[name] = pAudioFile;

  return false;
}

bool AndroidSoundManager::loadMusic(string const& path) {
  return loadAudioFile(path, path);
}

bool AndroidSoundManager::loadSoundEffect(string const& name,
                                          string const& path) {
  return loadAudioFile(name, path);
}

oboe::DataCallbackResult AndroidSoundManager::onAudioReady(
    oboe::AudioStream* audioStream, void* audioData, int32_t framesCount) {
  if (m_pCurrentSound == nullptr) {
    return oboe::DataCallbackResult::Continue;
  }

  int16_t* oboeBuffer = reinterpret_cast<int16_t*>(audioData);
  uint bufferSize =
      framesCount * audioStream->getChannelCount() * sizeof(int16_t);

  // Clear the buffer efficiently
  memset(oboeBuffer, 0, bufferSize);

  CurrentSound* pCurrentSound = m_pCurrentSound;

  while (pCurrentSound != nullptr) {
    AudioFile<int16_t>* pCurrentAudio = pCurrentSound->pAudio;
    int numSamples = pCurrentAudio->getNumSamplesPerChannel();

    for (int i = 0; i < framesCount && pCurrentSound->sampleIndex < numSamples;
         ++i) {
      for (int channel = 0; channel < audioStream->getChannelCount();
           ++channel) {
        // Calculate the target buffer index considering channel count
        int bufferIndex = (i * audioStream->getChannelCount()) + channel;

        if (bufferIndex < bufferSize / sizeof(int16_t)) {
          int32_t newValue =
              static_cast<int32_t>(oboeBuffer[bufferIndex]) +
              static_cast<int32_t>(
                  pCurrentAudio->samples[channel][pCurrentSound->sampleIndex] *
                  pCurrentSound->volume);

          oboeBuffer[bufferIndex] = clipToRangeInteger16(newValue);
        }
      }
      pCurrentSound->sampleIndex++;
    }

    if (pCurrentSound->sampleIndex >= numSamples) {
      if (pCurrentSound->loop) {
        pCurrentSound->sampleIndex = 0;
      } else {
        // End of the file, remove the sound
        removeSound(pCurrentAudio);
      }
    }
    pCurrentSound = pCurrentSound->pNext;
  }

  if (m_pCurrentSound == nullptr) {
    m_pStream->requestStop();
    return oboe::DataCallbackResult::Stop;
  }

  return oboe::DataCallbackResult::Continue;
}

void AndroidSoundManager::appendSound(AudioFile<int16_t>* pAudio, bool loop,
                                      float volume) {
  auto pCurrentSound = new CurrentSound();
  pCurrentSound->pAudio = pAudio;
  pCurrentSound->sampleIndex = 0;
  pCurrentSound->loop = loop;
  pCurrentSound->volume = volume;

  if (m_pCurrentSound == nullptr) {
    m_pCurrentSound = pCurrentSound;
    return;
  }

  CurrentSound* pCur = m_pCurrentSound;
  while (pCur->pNext != nullptr) {
    pCur = pCur->pNext;
  }

  pCur->pNext = pCurrentSound;
  pCurrentSound->pPrevious = pCur;
}

void AndroidSoundManager::removeSound(AudioFile<int16_t>* pAudio) {
  CurrentSound* pCur = m_pCurrentSound;
  CurrentSound* pPrevious = nullptr;

  while (pCur != nullptr) {
    if (pCur->pAudio == pAudio) {
      if (pPrevious) {
        pPrevious->pNext = pCur->pNext;
      } else {
        m_pCurrentSound = pCur->pNext;
      }

      if (pCur->pNext) {
        pCur->pNext->pPrevious = pPrevious;
      }

      delete pCur;
      return;
    }

    pPrevious = pCur;
    pCur = pCur->pNext;
  }
}