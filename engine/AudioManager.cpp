#include "AudioManager.h"
#include "lib/miniaudio_libopus.h"
#include <random>

AudioManager* AudioManager::s_instance = nullptr;

AudioManager::AudioManager()
{

  // ma_decoding_backend_vtable* pCustomBackendVTables[] = {
  //     ma_decoding_backend_libopus};

  // MiniAudio.GetResourceManager()->config.ppCustomDecodingBackendVTables =
  //     pCustomBackendVTables;

  BackgroundMusicIDs.push_back(
      RegisterNewSound("assets/sounds/music/Hip-HopLoop.ogg"));
}

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

void AudioManager::StartBackgroundMusic()
{
  std::random_device RandomDevice;
  std::mt19937 Generator(RandomDevice());
  std::uniform_int_distribution<> Distribution(0,
                                               BackgroundMusicIDs.size() - 1);

  int Index = Distribution(Generator);

  CurrentlyPlayingBackgroundID = BackgroundMusicIDs[Index];
  PlaySound(CurrentlyPlayingBackgroundID, true);
}

void AudioManager::StopBackgroundMusic()
{
  MiniAudio.Stop(CurrentlyPlayingBackgroundID);
}

void AudioManager::Tick() {}
