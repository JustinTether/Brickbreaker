#include "GameState.h"
#include "BaseBrick.h"
#include "engine.h"
#include "obj/Ball.h"
#include "obj/Bat.h"
#include "ui/GameOverMenu.h"
#include "ui/Hud.h"
#include "ui/MainMenu.h"
#include "ui/PauseMenu.h"
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
}

void GameStateObject::InitializeGameState()
{
  ResetGame();
  Engine::Get()->ClearAllGameObjects();

  std::shared_ptr<BaseObject> PlayerBat = std::make_shared<Bat>(Engine::Get());
  Engine::Get()->AddNewGameObject(PlayerBat);

  std::shared_ptr<BaseObject> GameBall = std::make_shared<Ball>(Engine::Get());
  Engine::Get()->AddNewGameObject(GameBall);

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
      InitializeGameState();
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
    break;

  case EGameState::END_GAME:
    if (!GameOverMenuObject->bIsInitialized)
      GameOverMenuObject->Initialize(Engine::Get());

    GameOverMenuObject->Draw(Engine::Get());

    if (GameOverMenuObject->bIsNewGameButtonPressed)
    {
      Engine::Get()->AudioManager.Toggle(GameOverMenuObject->ClickSound);
      InitializeGameState();
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

void GameStateObject::ApplyRandomUpgrade()
{
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
