#include "AudioManager.h"
#include "lib/miniaudio_libopus.h"
#include <random>

AudioManager* AudioManager::s_instance = nullptr;
float AudioManager::MusicVolume = 1.0f;
float AudioManager::EffectsVolume = 1.0f;

AudioManager::AudioManager()
{

  // ma_decoding_backend_vtable* pCustomBackendVTables[] = {
  //     ma_decoding_backend_libopus};

  // MiniAudio.GetResourceManager()->config.ppCustomDecodingBackendVTables =
  //     pCustomBackendVTables;

  BackgroundMusicIDs.push_back(
      RegisterNewSound("assets/sounds/music/Hip-HopLoop.ogg", false));
  BackgroundMusicIDs.push_back(
      RegisterNewSound("assets/sounds/music/CrunchyBassLoop.ogg", false));
  BackgroundMusicIDs.push_back(
      RegisterNewSound("assets/sounds/music/Space-SynthLoop.ogg", false));
  BackgroundMusicIDs.push_back(
      RegisterNewSound("assets/sounds/music/Space-SynthLoop02.ogg", false));
  BackgroundMusicIDs.push_back(
      RegisterNewSound("assets/sounds/music/TripleHatLoop.ogg", false));

  // SetMusicVolume(0.5f);
  SetEffectsVolume(0.5f);
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

const int& AudioManager::RegisterNewSound(std::string SoundFilePath,
                                          bool bIsEffect)
{
  int SoundID;
  SoundID = MiniAudio.LoadSound(SoundFilePath);

  if (bIsEffect)
    MiniAudio.SetVolume(SoundID, EffectsVolume);

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

void AudioManager::SetMusicVolume(float InNewVolume)
{
  MiniAudio.SetVolume(CurrentlyPlayingBackgroundID, InNewVolume);
  MusicVolume = InNewVolume;
}

void AudioManager::SetEffectsVolume(float InNewVolume)
{
  for (int ID : RegisteredSoundIDs)
  {
    if (ID != CurrentlyPlayingBackgroundID)
      MiniAudio.SetVolume(ID, InNewVolume);
  }

  EffectsVolume = InNewVolume;
}

float AudioManager::GetMusicVolume() { return MusicVolume; }

float AudioManager::GetEffectsVolume() { return EffectsVolume; }
