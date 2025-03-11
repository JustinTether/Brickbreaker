#include "GameState.h"

GameStateObject::GameStateObject()
{
  CurrentGameState = EGameState::MAIN_MENU;
  NumBallsRemaining = 3;
}

EGameState GameStateObject::GetCurrentState()
{
  return CurrentGameState;
}

void GameStateObject::SetCurrentState(EGameState NewState)
{
  CurrentGameState = NewState;
}

int GameStateObject::GetNumBallsRemaining()
{
  return NumBallsRemaining;
}

void GameStateObject::SetNumBallsRemaining(int Num)
{
  NumBallsRemaining = Num;
}
