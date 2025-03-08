#ifndef ENGINE_H
#define ENGINE_H
#pragma once
#include "../lib/olcPixelGameEngine.h"
#include "../lib/olcPGEX_QuickGUI.h"
#include "../lib/olcPGEX_MiniAudio.h"
class Bat;
class Ball;
class MainMenuGUI;
class PauseMenu;
class BaseBrick;

enum EGameState 
{
    MAIN_MENU,
    PAUSED,
    GAME_LOOP,
    END_ROUND,
};

class Engine : public olc::PixelGameEngine
{
    public:

      Ball* GameBall;
      MainMenuGUI* MainMenuObject;
      PauseMenu* PauseMenuObject;
      olc::QuickGUI::Manager GuiManager;
      olc::vi2d TileSize = {16, 16};
      std::vector<BaseBrick*> Bricks;


      olc::vf2d PotentialBallPos = olc::vf2d();
      olc::vf2d TileBallRadialDims = olc::vf2d();
      int MapWidth = 24;
      int MapHeight = 30;

      std::unique_ptr<olc::Sprite> TileSheet;
      
      // Audio Manager through MiniAudio
      olc::MiniAudio AudioManager;

    public:
      Engine();

      Bat* UserBat;
      EGameState GameState = EGameState::MAIN_MENU;


    virtual bool OnUserCreate() override;
    virtual bool OnUserUpdate(float fElapsedTime) override;
    bool TestResolveCollisionPoint(const olc::vf2d& point);
    int main();

};
#endif

