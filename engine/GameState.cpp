#include "GameState.h"
#include "engine.h"
#include <random>

GameStateObject::GameStateObject()
{
  CurrentGameState = EGameState::MAIN_MENU;
  NumBallsRemaining = 3;
  UpgradeFactoryObject = std::make_shared<UpgradeFactory>();

  // Register UpgradeFactory types
  UpgradeFactoryObject->RegisterUpgrade(
      "IncreaseBatWidthUpgrade",
      []() { return std::make_shared<IncreaseBatWidthUpgrade>(10.0, 100.0); });
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
  std::random_device RandomDevice;
  std::mt19937 Generator(RandomDevice());

  const std::vector<std::string> AvailableUpgrades =
      UpgradeFactoryObject->GetRegisteredUpgrades();

  std::uniform_int_distribution<> Distrobution(0, AvailableUpgrades.size() - 1);
  int RandomIndex = Distrobution(Generator);

  std::string ChosenUpgradeType = AvailableUpgrades[RandomIndex];
  std::shared_ptr<BaseUpgrade> ChosenUpgrade =
      UpgradeFactoryObject->CreateUpgrade(ChosenUpgradeType);

  Engine::Get()->AddNewGameObject(ChosenUpgrade);
}
