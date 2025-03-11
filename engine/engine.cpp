#include "engine.h"
#include "../obj/Ball.h"
#include "../obj/Bat.h"
#include "../ui/MainMenu.h"
#include "../ui/PauseMenu.h"
#include "../ui/Hud.h"
#include "../lib/olcPGEX_QuickGUI.h"
#include "Clay_Renderer_PGE.h"
#include "../obj/BaseBrick.h"
#include "GameState.h"

#define OLC_PGEX_SOUND_H

Engine::Engine()
{
  sAppName = "BrickBreaker";
}

void Engine::HandleClayErrors(Clay_ErrorData ErrorData)
{
  std::cout << ErrorData.errorText.chars << "\n";
}

bool Engine::OnUserCreate() 
{
  UserBat = new Bat(this);
  GameBall = new Ball(this);
  MainMenuObject = new MainMenuGUI();
  PauseMenuObject = new PauseMenu();
  HudObject = new Hud();
  GameState = new GameStateObject();
  GuiManager.colNormal = olc::YELLOW;
  TileSheet = std::make_unique<olc::Sprite>("../assets/sprites/tileset-01.png");

  // Initialize Clay for use
  ClayRenderer = new ClayPGERenderer();
  uint64_t TotalClayMemory = Clay_MinMemorySize();
  Clay_Arena Arena = Clay_CreateArenaWithCapacityAndMemory(TotalClayMemory, malloc(TotalClayMemory));
  Clay_Initialize(Arena, (Clay_Dimensions){static_cast<float>(ScreenWidth()), static_cast<float>(ScreenHeight())}, (Clay_ErrorHandler){HandleClayErrors});
  Clay_SetMeasureTextFunction(&ClayPGERenderer::MeasureText, nullptr);


  // Initialize our bricks grid
  for (int y = 0; y < MapHeight; y++)
  {
    for (int x = 0; x < MapWidth; x++)
    {
      BaseBrick* NewBrick = new BaseBrick();

      if(x == 0 || y == 0 || x == MapWidth-1)
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

  return true;
}


bool Engine::OnUserUpdate(float fElapsedTime)
{
    // Clear previous frame
    Clear(olc::BLACK);
    
    switch(GameState->GetCurrentState())
    {
        case EGameState::MAIN_MENU:
            if (MainMenuObject && !MainMenuObject->bIsInitialized)
            {
                MainMenuObject->Initialize(this);
                return true;
            }

            MainMenuObject->MainMenuManager.Update(this);
            if (MainMenuObject->MainMenuStartButton->bPressed)
            {
                //AudioManager.PlayWaveform(MainMenuObject->ClickSound);
                AudioManager.Toggle(MainMenuObject->ClickSound);
                GameState->SetCurrentState(EGameState::GAME_LOOP);
            }
              MainMenuObject->Draw(this);
            //MainMenuObject->MainMenuManager.Draw(this);
            //DrawString(ScreenWidth()/4, ScreenHeight()/2-20, "BrickBreaker", olc::WHITE, 2);

        break;

        case EGameState::PAUSED:
          if(PauseMenuObject && !PauseMenuObject->bIsInitialized)
          {
            GuiManager = olc::QuickGUI::Manager();
            PauseMenuObject->Initialize(this, GuiManager);
            return true;
          }

          GuiManager.Update(this);
          if(PauseMenuObject->ResumeButton->bPressed || GetKey(olc::Key::ESCAPE).bPressed)
          {
            GameState->SetCurrentState(EGameState::GAME_LOOP);
            return true;
          }

          GuiManager.Draw(this);
        break;

        case EGameState::GAME_LOOP:
        {
          if (HudObject && !HudObject->bIsInitialized)
          {
            HudObject->Initialize(this);
          }

          // Update the HUD and draw it
          HudObject->BallsRemainingNumber->sText = std::to_string(GameState->GetNumBallsRemaining());
          HudObject->HudManager.Update(this);
          HudObject->HudManager.Draw(this);
          

          // if we're out of balls, end the game
          if (GameState->GetNumBallsRemaining() < 0)
          {
            GameState->SetCurrentState(EGameState::END_GAME);
            return true;
          }

          if(GetKey(olc::Key::ESCAPE).bPressed)
          {
            GameState->SetCurrentState(EGameState::PAUSED);
            return true;
          }

         // Draw the map
          SetPixelMode(olc::Pixel::MASK); // Dont draw pixels which have any transparency
          for (int y = 0; y < MapHeight; y++)
          {
              for (int x = 0; x < MapWidth; x++)
              {
                  BaseBrick* NewBrick = Bricks[y * MapWidth + x];
                  
                  if(NewBrick->bIsAir)
                    // Do nothing with air bricks, they're not rendered
                    continue;

                  DrawPartialSprite(olc::vi2d(x, y) * TileSize, TileSheet.get(), olc::vi2d(NewBrick->MaxHits, 0) * TileSize, TileSize);

              }
          }
          SetPixelMode(olc::Pixel::NORMAL);

          UserBat->Tick(this, fElapsedTime);
          GameBall->Tick(this, fElapsedTime);

        // Draw round state
        
            
        }break;

        case EGameState::END_ROUND:
        break;
    }

    return true;
}

