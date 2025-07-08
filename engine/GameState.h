#pragma once
#include "lib/cereal/archives/portable_binary.hpp"
#include "lib/olcPixelGameEngine.h"
#include "upgrades/BaseUpgrade.h"
#include "upgrades/UpgradeFactory.h"

#include <vector>
class Engine;
class MainMenuGUI;
class GameOverGUI;
class PauseMenu;
class Hud;
class OptionsMenu;

enum EGameState
{
  MAIN_MENU,
  PAUSED,
  OPTIONS,
  GAME_LOOP,
  END_ROUND,
  END_GAME
};

struct SaveStateAudioLevels
{
  float EffectsVolume;
  float MusicVolume;

  template <class Archive> void serialize(Archive& archive)
  {
    archive(EffectsVolume, MusicVolume);
  }
};

struct SaveState
{
  SaveStateAudioLevels AudioLevels;

  template <class Archive> void save(Archive& archive) const
  {
    archive(AudioLevels);
  }

  template <class Archive> void load(Archive& archive) { archive(AudioLevels); }
};

class GameStateObject
{
public:
  GameStateObject();

protected:
  int NumBallsRemaining = 0;
  EGameState CurrentGameState;
  std::vector<std::shared_ptr<BaseUpgrade>> AvailableUpgrades;

public:
  void SetCurrentState(EGameState NewState);
  EGameState GetCurrentState();
  int GetNumBallsRemaining();
  void SetNumBallsRemaining(int Num);
  int GetNumBricksRemaining();
  void SetNumBricksRemaining(int InBricksRemaning);
  bool IsGameOver();
  void ResetGame();
  void Tick(float DeltaTime);
  void ApplyRandomUpgrade();
  void InitializeGameState(bool bShouldReset);
  SaveState& GetSaveStateData();
  void LoadGameState();
  void SaveGameState();
  void SetGameState(SaveState& SaveGameData);
  void CreateNewUpgrade(olc::vf2d StartingPosition);
  void ApplyUpgrade(BaseUpgrade* UpgradeToApply);

  int MapWidth = 24;
  int MapHeight = 30;
  // olc::vi2d TileSize = {16, 16};

private:
  std::shared_ptr<UpgradeFactory> UpgradeFactoryObject;
  MainMenuGUI* MainMenuObject;
  PauseMenu* PauseMenuObject;
  GameOverGUI* GameOverMenuObject;
  OptionsMenu* OptionsMenuObject;
  Hud* HudObject;
  void GenerateRandomLevel();
  int NumBricksForLevel;
  int BackgroundLoopID;
  SaveState SaveStateData;
};
