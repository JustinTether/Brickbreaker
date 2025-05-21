#include "GameState.h"
#include "engine.h"

GameStateObject::GameStateObject()
{
  CurrentGameState = EGameState::MAIN_MENU;
  NumBallsRemaining = 3;
  std::shared_ptr<BaseUpgrade> IncreaseBatWidth =
      std::static_pointer_cast<BaseUpgrade>(
          std::make_shared<IncreaseBatWidthUpgrade>(10.0, 100.0));

  AvailableUpgrades.push_back(IncreaseBatWidth);
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

void GameStateObject::ApplyRandomUpgrade()
{
  Engine* Engine = Engine::Get();

  std::shared_ptr<BaseUpgrade> ChosenUpgrade;
}
