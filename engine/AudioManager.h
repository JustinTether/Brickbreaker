#pragma once
#include "engine/engine.h"
#include "lib/olcPGEX_MiniAudio.h"
#include <string>
#include <vector>

class AudioManager
{
public:
  // Singleton management
  AudioManager();
  AudioManager(const AudioManager&) = delete;
  AudioManager& operator=(const AudioManager&) = delete;
  static AudioManager* Get();

  void PlaySound(int InSoundID, bool bShouldLoop = false);
  const int& RegisterNewSound(std::string SoundFilePath);

private:
  static AudioManager* s_instance;

  // Audio Manager through MiniAudio
  olc::MiniAudio MiniAudio;

  float GlobalVolume;
  std::vector<int> RegisteredSoundIDs;
};