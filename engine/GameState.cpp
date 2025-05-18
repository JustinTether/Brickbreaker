#include "GameState.h"

GameStateObject::GameStateObject()
{
  CurrentGameState = EGameState::MAIN_MENU;
  NumBallsRemaining = 3;
}

void GameStateObject::ResetGame() { NumBallsRemaining = 3; }

EGameState GameStateObject::GetCurrentState() { return CurrentGameState; }

int GameStateObject::GetNumBallsRemaining() { return NumBallsRemaining; }

void GameStateObject::SetNumBallsRemaining(int Num) { NumBallsRemaining = Num; }

bool GameStateObject::IsGameOver() { return NumBallsRemaining <= 0; }

void GameStateObject::SetCurrentState(EGameState NewState)
{
  CurrentGameState = NewState;
}
