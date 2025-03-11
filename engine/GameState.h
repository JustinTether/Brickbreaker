#pragma once

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
  int NumBallsRemaining;
  EGameState CurrentGameState;

public:
  void SetCurrentState(EGameState NewState);
  EGameState GetCurrentState();
  int GetNumBallsRemaining();
  void SetNumBallsRemaining(int Num);
};
