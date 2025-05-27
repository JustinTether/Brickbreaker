#include "GameState.h"
#include "BaseBrick.h"
#include "engine.h"
#include "obj/Ball.h"
#include "obj/Bat.h"
#include "ui/GameOverMenu.h"
#include "ui/Hud.h"
#include "ui/MainMenu.h"
#include "ui/PauseMenu.h"
#include "upgrades/IncreaseBatWidth.h"
#include "upgrades/NewBallsUpgrade.h"
#include <random>

GameStateObject::GameStateObject()
{
  CurrentGameState = EGameState::MAIN_MENU;
  NumBallsRemaining = 3;
  UpgradeFactoryObject = std::make_shared<UpgradeFactory>();
  MainMenuObject = new MainMenuGUI();
  PauseMenuObject = new PauseMenu();
  GameOverMenuObject = new GameOverGUI();
  HudObject = new Hud();

  // Register UpgradeFactory types
  UpgradeFactoryObject->RegisterUpgrade(
      "IncreaseBatWidthUpgrade",
      []() { return std::make_shared<IncreaseBatWidthUpgrade>(10.0, 100.0); });

  UpgradeFactoryObject->RegisterUpgrade(
      "ThreeNewBallsUpgrade",
      []() { return std::make_shared<NewBallsUpgrade>(10.0, 3); });
}

void GameStateObject::InitializeGameState(bool bShouldReset)
{
  if (bShouldReset)
    ResetGame();

  Engine::Get()->ClearAllGameObjects();

  std::shared_ptr<BaseObject> PlayerBat = std::make_shared<Bat>(Engine::Get());
  Engine::Get()->AddNewGameObject(PlayerBat);

  std::shared_ptr<BaseObject> GameBall = std::make_shared<Ball>(Engine::Get());
  Engine::Get()->AddNewGameObject(GameBall);

  if (true)
  {
    GenerateRandomLevel();
    return;
  }

  for (int y = 0; y < MapHeight; y++)
  {
    for (int x = 0; x < MapWidth; x++)
    {
      std::shared_ptr<BaseBrick> NewBrick = std::make_shared<BaseBrick>();

      if (x == 0 || y == 0 || x == MapWidth - 1)
      {
        NewBrick->bIsWall = true;
      }
      else
      {
        NewBrick->bIsAir = true;
        NewBrick->bIsWall = false;
      }

      if (x > 2 && x <= 20 && y > 3 && y <= 5)
      {
        NewBrick->bIsAir = false;
        NewBrick->TileOffset = 1;
        NewBrick->MaxHits = 1;
      }

      if (x > 2 && x <= 20 && y > 5 && y <= 7)
      {
        NewBrick->bIsAir = false;
        NewBrick->TileOffset = 2;
        NewBrick->MaxHits = 2;
      }

      if (x > 2 && x <= 20 && y > 7 && y <= 9)
      {
        NewBrick->bIsAir = false;
        NewBrick->TileOffset = 3;
        NewBrick->MaxHits = 3;
      }

      NewBrick->XPosition = x;
      NewBrick->YPosition = y;
      Engine::Get()->AddNewGameObject(
          std::static_pointer_cast<BaseObject>(NewBrick));
    }
  }
}

// Mostly used for debugging or a 'random' mode, these aren't going to be
// garaunteed fun or optimized levels
void GameStateObject::GenerateRandomLevel()
{

  std::random_device RandomDevice;
  std::mt19937 Generator(RandomDevice());
  std::uniform_int_distribution<> BlockDistribution(1, 3);
  std::uniform_int_distribution<> AirDistribution(0, 1);
  int NumBricks = 0;

  for (int y = 0; y < MapHeight; y++)
  {
    for (int x = 0; x < MapWidth; x++)
    {
      std::shared_ptr<BaseBrick> NewBrick = std::make_shared<BaseBrick>();

      if (x == 0 || y == 0 || x == MapWidth - 1)
      {
        NewBrick->bIsWall = true;
      }
      else
      {
        NewBrick->bIsAir = true;
        NewBrick->bIsWall = false;
      }

      if (x > 2 && x <= 20 && y > 3 && y <= 9)
      {

        NewBrick->bIsAir = static_cast<bool>(AirDistribution(Generator));
        NewBrick->MaxHits = BlockDistribution(Generator);
        NewBrick->TileOffset = NewBrick->MaxHits;

        if (!NewBrick->bIsAir)
          NumBricks++;
      }

      NewBrick->XPosition = x;
      NewBrick->YPosition = y;
      Engine::Get()->AddNewGameObject(
          std::static_pointer_cast<BaseObject>(NewBrick));
    }
  }

  SetNumBricksRemaining(NumBricks);
}

void GameStateObject::Tick(float DeltaTime)
{
  switch (GetCurrentState())
  {
  case EGameState::MAIN_MENU:
    if (MainMenuObject && !MainMenuObject->bIsInitialized)
    {
      MainMenuObject->Initialize(Engine::Get());
      return;
    }

    if (MainMenuObject->bIsStartButtonPressed)
    {
      // AudioManager.PlayWaveform(MainMenuObject->ClickSound);
      InitializeGameState(true);
      Engine::Get()->AudioManager.Toggle(MainMenuObject->ClickSound);
      SetCurrentState(EGameState::GAME_LOOP);
    }
    MainMenuObject->Draw(Engine::Get());

    break;

  case EGameState::PAUSED:
    if (PauseMenuObject && !PauseMenuObject->bIsInitialized)
    {
      PauseMenuObject->Initialize(Engine::Get());
      return;
    }

    if (PauseMenuObject->bIsResumeButtonClicked ||
        Engine::Get()->GetKey(olc::Key::ESCAPE).bPressed)
    {
      Engine::Get()->AudioManager.Toggle(PauseMenuObject->ClickSound);
      PauseMenuObject->bIsResumeButtonClicked = false;
      SetCurrentState(EGameState::GAME_LOOP);
      return;
    }

    PauseMenuObject->Draw(Engine::Get());
    break;

  case EGameState::GAME_LOOP:
  {
    if (HudObject && !HudObject->bIsInitialized)
    {
      HudObject->Initialize(Engine::Get());
    }

    // Update the HUD and draw it
    HudObject->Draw(Engine::Get());

    // if we're out of balls, end the game
    if (GetNumBallsRemaining() < 0)
    {
      SetCurrentState(EGameState::END_GAME);
      return;
    }

    // If we've completed the level, end the round (Probably show end_round
    // stats, and then initiate new level)
    if (GetNumBricksRemaining() <= 0)
    {
      SetCurrentState(EGameState::END_ROUND);
      return;
    }

    if (Engine::Get()->GetKey(olc::Key::ESCAPE).bPressed)
    {
      SetCurrentState(EGameState::PAUSED);
      return;
    }
    // Check for end-round conditions
    if (IsGameOver())
    {
      SetCurrentState(EGameState::END_GAME);
    }
  }
  break;

  case EGameState::END_ROUND:
    InitializeGameState(false);
    SetCurrentState(EGameState::GAME_LOOP);
    break;

  case EGameState::END_GAME:
    if (!GameOverMenuObject->bIsInitialized)
      GameOverMenuObject->Initialize(Engine::Get());

    GameOverMenuObject->Draw(Engine::Get());

    if (GameOverMenuObject->bIsNewGameButtonPressed)
    {
      Engine::Get()->AudioManager.Toggle(GameOverMenuObject->ClickSound);
      InitializeGameState(true);
      SetCurrentState(EGameState::GAME_LOOP);
      break;
    }

    if (GameOverMenuObject->bIsMainMenuButtonPressed)
    {
      Engine::Get()->AudioManager.Toggle(GameOverMenuObject->ClickSound);
      SetCurrentState(EGameState::MAIN_MENU);
      break;
    }

    break;
  }
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

int GameStateObject::GetNumBricksRemaining() { return NumBricksForLevel; }
void GameStateObject::SetNumBricksRemaining(int InNumBricks)
{
  NumBricksForLevel = InNumBricks;
}

void GameStateObject::ApplyRandomUpgrade()
{
  std::random_device RandomDevice;
  std::mt19937 Generator(RandomDevice());

  const std::vector<std::string> AvailableUpgrades =
      UpgradeFactoryObject->GetRegisteredUpgrades();

  std::uniform_int_distribution<> Distrobution(0, AvailableUpgrades.size() - 1);
  int RandomIndex = Distrobution(Generator);

  std::string ChosenUpgradeType = AvailableUpgrades[RandomIndex];

  // Check if an upgrade of this type already exists and is active, if so, we
  // want to refresh it instead of adding another!
  std::vector<std::shared_ptr<BaseObject>> Upgrades =
      Engine::Get()->GetGameObjectOfType<BaseUpgrade>();

  for (auto Obj : Upgrades)
  {
    if (std::shared_ptr<BaseUpgrade> Upgrade =
            std::dynamic_pointer_cast<BaseUpgrade>(Obj))
    {
      if (Upgrade->Name == ChosenUpgradeType)
      {
        Upgrade->Reset();
        return;
      }
    }
  }

  // Otherwise, we just add a new upgrade
  std::shared_ptr<BaseUpgrade> ChosenUpgrade =
      UpgradeFactoryObject->CreateUpgrade(ChosenUpgradeType);

  // Set the Name of the object to the stringified type name for later use in
  // debug UI
  ChosenUpgrade->Name = ChosenUpgradeType;

  Engine::Get()->AddNewGameObject(ChosenUpgrade);
}
