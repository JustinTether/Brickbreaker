#pragma once
#include "upgrades/BaseUpgrade.h"
#include "upgrades/IncreaseBatWidth.h"
#include <vector>
class Engine;
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
  bool IsGameOver();
  void ResetGame();

  void ApplyRandomUpgrade();
};
