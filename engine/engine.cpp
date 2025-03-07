#include "engine.h"
#include "../obj/Ball.h"
#include "../obj/Bat.h"
#include "../ui/MainMenu.h"
#include "../ui/PauseMenu.h"
#include "../lib/olcPGEX_QuickGUI.h"

#define OLC_PGEX_SOUND_H

Engine::Engine()
{
  sAppName = "BrickBreaker";
}

bool Engine::OnUserCreate() 
{
  UserBat = new Bat(this);
  GameBall = new Ball(this);

  MainMenuObject = new MainMenuGUI();
  PauseMenuObject = new PauseMenu();

  GuiManager.colNormal = olc::YELLOW;

  TileSheet = std::make_unique<olc::Sprite>("./assets/sprites/tileset-01.png");

  // Initialize our tile grid
  Tiles = std::make_unique<int[]>(MapWidth * MapHeight);

  // Initialize the int array map with either 0 or 10, 10 being the boundary walls
  for (int y = 0; y < MapHeight; y++)
    {
      for (int x = 0; x < MapWidth; x++)
        {
          if (x == 0 || y == 0 || x == MapWidth-1)
            Tiles[y * MapWidth + x] = 10;
          else
            Tiles[y * MapWidth + x] = 0;

          if (x > 2 && x <= 20 && y > 3 && y <= 5)
            Tiles[y * MapWidth + x] = 1;

          if (x > 2 && x <= 20 && y > 5 && y <= 7)
            Tiles[y * MapWidth + x] = 2;

          if (x > 2 && x <= 20 && y > 7 && y <= 9)
            Tiles[y * MapWidth + x] = 3;

        }
    }

    return true;
}

bool Engine::OnUserUpdate(float fElapsedTime)
{
    // Clear previous frame
    Clear(olc::BLACK);
    
    switch(GameState)
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
                GameState = EGameState::GAME_LOOP;
            }

            MainMenuObject->MainMenuManager.Draw(this);
            DrawString(ScreenWidth()/4, ScreenHeight()/2-20, "BrickBreaker", olc::WHITE, 2);

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
            GameState = EGameState::GAME_LOOP;
            return true;
          }

          GuiManager.Draw(this);
        break;

        case EGameState::GAME_LOOP:
        {
            if(GetKey(olc::Key::ESCAPE).bPressed)
            {
              GameState = EGameState::PAUSED;
              return true;
            }

           // Draw the map
            SetPixelMode(olc::Pixel::MASK); // Dont draw pixels which have any transparency
            for (int y = 0; y < MapHeight; y++)
            {
                for (int x = 0; x < MapWidth; x++)
                {
                    switch (Tiles[y * MapWidth + x])
                    {
                    case 0: // Do nothing
                        break;
                    case 10: // Draw Boundary
                        DrawPartialSprite(olc::vi2d(x, y) * TileSize, TileSheet.get(), olc::vi2d(0, 0) * TileSize, TileSize);
                        break;

                    case 1: 
                        DrawPartialSprite(olc::vi2d(x, y) * TileSize, TileSheet.get(), olc::vi2d(1, 0) * TileSize, TileSize);
                        break;

                    case 2: 
                        DrawPartialSprite(olc::vi2d(x, y) * TileSize, TileSheet.get(), olc::vi2d(2, 0) * TileSize, TileSize);
                        break;

                    case 3: 
                        DrawPartialSprite(olc::vi2d(x, y) * TileSize, TileSheet.get(), olc::vi2d(3, 0) * TileSize, TileSize);
                        break;
                    }
                }
            }
            SetPixelMode(olc::Pixel::NORMAL);

            UserBat->Tick(this, fElapsedTime);
            GameBall->Tick(this, fElapsedTime);
            
        }break;

        case EGameState::END_ROUND:
        break;
    }

    return true;
}

