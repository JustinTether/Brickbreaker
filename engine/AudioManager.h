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
  const int& RegisterNewSound(std::string SoundFilePath, bool bIsEffect = true);
  void StartBackgroundMusic();
  void StopBackgroundMusic();
  void Tick();
  void SetMusicVolume(float InNewVolume);
  void SetEffectsVolume(float InNewVolume);
  static float GetMusicVolume();
  static float GetEffectsVolume();

private:
  static AudioManager* s_instance;

  // Audio Manager through MiniAudio
  olc::MiniAudio MiniAudio;

  static float EffectsVolume;
  static float MusicVolume;
  std::vector<int> RegisteredSoundIDs;
  std::vector<int> BackgroundMusicIDs;
  int CurrentlyPlayingBackgroundID;
};