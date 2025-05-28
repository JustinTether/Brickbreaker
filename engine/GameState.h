#pragma once
#include "lib/olcPixelGameEngine.h"
#include "upgrades/BaseUpgrade.h"
#include "upgrades/UpgradeFactory.h"

#include <vector>
class Engine;
class MainMenuGUI;
class GameOverGUI;
class PauseMenu;
class Hud;

enum EGameState
{
  MAIN_MENU,
  PAUSED,
  GAME_LOOP,
  END_ROUND,
  END_GAME
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

  int MapWidth = 24;
  int MapHeight = 30;
  // olc::vi2d TileSize = {16, 16};

private:
  std::shared_ptr<UpgradeFactory> UpgradeFactoryObject;
  MainMenuGUI* MainMenuObject;
  PauseMenu* PauseMenuObject;
  GameOverGUI* GameOverMenuObject;
  Hud* HudObject;
  void GenerateRandomLevel();
  int NumBricksForLevel;
  int BackgroundLoopID;
};
