#include "AudioManager.h"

AudioManager* AudioManager::s_instance = nullptr;

AudioManager::AudioManager() {}

AudioManager* AudioManager::Get()
{
  if (s_instance == nullptr)
  {
    s_instance = new AudioManager();
  }

  return s_instance;
}

void AudioManager::PlaySound(int InSoundID, bool bShouldLoop)
{
  MiniAudio.Play(InSoundID, bShouldLoop);
}

const int& AudioManager::RegisterNewSound(std::string SoundFilePath)
{
  int SoundID;
  SoundID = MiniAudio.LoadSound(SoundFilePath);

  RegisteredSoundIDs.push_back(SoundID);

  return RegisteredSoundIDs.back();
}
