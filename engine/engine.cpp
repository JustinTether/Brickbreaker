#include "engine.h"
#include "../lib/olcPGEX_QuickGUI.h"
#include "../obj/Ball.h"
#include "../obj/BaseBrick.h"
#include "../obj/Bat.h"
#include "../ui/Hud.h"
#include "../ui/MainMenu.h"
#include "../ui/PauseMenu.h"
#include "Clay_Renderer_PGE.h"
#include "GameState.h"
#include "ui/GameOverMenu.h"
#include <memory>

#include "obj/upgrades/IncreaseBatWidth.h"

#define OLC_PGEX_SOUND_H

Engine::Engine() { sAppName = "BrickBreaker"; }

void Engine::HandleClayErrors(Clay_ErrorData ErrorData)
{
  std::cout << ErrorData.errorText.chars << "\n";
}

bool Engine::OnUserCreate()
{
  // Persistent menu pointers, these carry over between games/rounds
  MainMenuObject = new MainMenuGUI();
  PauseMenuObject = new PauseMenu();
  GameOverMenuObject = new GameOverGUI();
  HudObject = new Hud();
  GameState = new GameStateObject();
  GuiManager.colNormal = olc::YELLOW;
  TileSheet = std::make_unique<olc::Sprite>("../assets/sprites/tileset-01.png");

  // std::shared_ptr<IncreaseBatWidthUpgrade> WidthUpgrade =
  // std::make_shared<IncreaseBatWidthUpgrade>(10.0f, 850.0f);

  // Initialize Clay for use
  ClayRenderer = new ClayPGERenderer();
  uint64_t TotalClayMemory = Clay_MinMemorySize();
  Clay_Arena Arena = Clay_CreateArenaWithCapacityAndMemory(
      TotalClayMemory, malloc(TotalClayMemory));
  Clay_Initialize(Arena,
                  (Clay_Dimensions){static_cast<float>(ScreenWidth()),
                                    static_cast<float>(ScreenHeight())},
                  (Clay_ErrorHandler){HandleClayErrors});
  Clay_SetMeasureTextFunction(&ClayPGERenderer::MeasureText, nullptr);

  InitializeGameState();
  return true;
}

void Engine::InitializeGameState()
{
  GameState->ResetGame();
  GameObjects.clear();

  std::shared_ptr<Bat> PlayerBat = std::make_shared<Bat>(this);
  GameObjects.push_back(std::static_pointer_cast<BaseObject>(PlayerBat));

  std::shared_ptr<Ball> GameBall = std::make_shared<Ball>(this);
  GameObjects.push_back(std::static_pointer_cast<BaseObject>(GameBall));

  // Clear any remaining brick states
  Bricks.clear();

  for (int y = 0; y < MapHeight; y++)
  {
    for (int x = 0; x < MapWidth; x++)
    {
      BaseBrick* NewBrick = new BaseBrick();

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
      Bricks.push_back(NewBrick);
    }
  }
}

bool Engine::OnUserUpdate(float fElapsedTime)
{
  // Clear previous frame
  Clear(olc::BLACK);

  switch (GameState->GetCurrentState())
  {
  case EGameState::MAIN_MENU:
    if (MainMenuObject && !MainMenuObject->bIsInitialized)
    {
      MainMenuObject->Initialize(this);
      return true;
    }

    if (MainMenuObject->bIsStartButtonPressed)
    {
      // AudioManager.PlayWaveform(MainMenuObject->ClickSound);
      InitializeGameState();
      AudioManager.Toggle(MainMenuObject->ClickSound);
      GameState->SetCurrentState(EGameState::GAME_LOOP);
    }
    MainMenuObject->Draw(this);

    break;

  case EGameState::PAUSED:
    if (PauseMenuObject && !PauseMenuObject->bIsInitialized)
    {
      PauseMenuObject->Initialize(this);
      return true;
    }

    if (PauseMenuObject->bIsResumeButtonClicked ||
        GetKey(olc::Key::ESCAPE).bPressed)
    {
      AudioManager.Toggle(PauseMenuObject->ClickSound);
      PauseMenuObject->bIsResumeButtonClicked = false;
      GameState->SetCurrentState(EGameState::GAME_LOOP);
      return true;
    }

    PauseMenuObject->Draw(this);
    break;

  case EGameState::GAME_LOOP:
  {
    if (GetKey(olc::Key::P).bPressed)
    {
      std::shared_ptr<IncreaseBatWidthUpgrade> BatWidthUpgrade =
          std::make_shared<IncreaseBatWidthUpgrade>(10.0f, 100.0f);
      GameObjects.push_back(
          std::static_pointer_cast<BaseObject>(BatWidthUpgrade));
    }

    if (HudObject && !HudObject->bIsInitialized)
    {
      HudObject->Initialize(this);
    }

    // Update the HUD and draw it
    HudObject->Draw(this);

    // if we're out of balls, end the game
    if (GameState->GetNumBallsRemaining() < 0)
    {
      GameState->SetCurrentState(EGameState::END_GAME);
      return true;
    }

    if (GetKey(olc::Key::ESCAPE).bPressed)
    {
      GameState->SetCurrentState(EGameState::PAUSED);
      return true;
    }

    // Draw the map
    SetPixelMode(
        olc::Pixel::MASK); // Dont draw pixels which have any transparency
    for (int y = 0; y < MapHeight; y++)
    {
      for (int x = 0; x < MapWidth; x++)
      {
        BaseBrick* NewBrick = Bricks[y * MapWidth + x];

        if (NewBrick->bIsAir)
          // Do nothing with air bricks, they're not rendered
          continue;

        DrawPartialSprite(olc::vi2d(x, y) * TileSize, TileSheet.get(),
                          olc::vi2d(NewBrick->MaxHits, 0) * TileSize, TileSize);
      }
    }
    SetPixelMode(olc::Pixel::NORMAL);

    // Tick all GameObjects
    for (std::shared_ptr<BaseObject> GameObj : GameObjects)
    {
      if (GameObj && GameObj->bShouldBeGCd)
        continue;

      GameObj->Tick(this, fElapsedTime);
    }
    // Draw round state

    // Check for end-round conditions
    if (GameState->IsGameOver())
    {
      GameState->SetCurrentState(EGameState::END_GAME);
    }
  }
  break;

  case EGameState::END_ROUND:
    break;

  case EGameState::END_GAME:
    if (!GameOverMenuObject->bIsInitialized)
      GameOverMenuObject->Initialize(this);

    GameOverMenuObject->Draw(this);

    if (GameOverMenuObject->bIsNewGameButtonPressed)
    {
      AudioManager.Toggle(GameOverMenuObject->ClickSound);
      InitializeGameState();
      GameState->SetCurrentState(EGameState::GAME_LOOP);
      break;
    }

    if (GameOverMenuObject->bIsMainMenuButtonPressed)
    {
      AudioManager.Toggle(GameOverMenuObject->ClickSound);
      GameState->SetCurrentState(EGameState::MAIN_MENU);
      break;
    }

    break;
  }

  return true;
}

void Engine::GCObjects()
{
  for (std::shared_ptr<BaseObject> GameObj : GameObjects)
  {
    if (GameObj && GameObj->bShouldBeGCd)
    {
      GameObjects.erase(
          std::remove(GameObjects.begin(), GameObjects.end(), GameObj),
          GameObjects.end());
    }
  }
}
