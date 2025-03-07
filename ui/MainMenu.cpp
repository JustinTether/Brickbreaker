#include "../lib/olcPGEX_QuickGUI.h"
#include "../lib/olcPGEX_MiniAudio.h"
#include "../engine/engine.h"
#include "MainMenu.h"

void MainMenuGUI::Initialize(Engine* EngineInstance)
{
  MainMenuStartButton = new olc::QuickGUI::Button(MainMenuManager,
    "Start",
    { ((float)EngineInstance->ScreenWidth()/2) - MainMenuButtonWidth/2, (float)EngineInstance->ScreenHeight()/2 },
    { MainMenuButtonWidth, MainMenuButtonHeight });

  MainMenuManager.colNormal = olc::BLUE;
  ClickSound = EngineInstance->AudioManager.LoadSound("../assets/sounds/click3.wav");

  //MainMenuText = new olc::QuickGUI::Label(GuiManager, "BrickBreaker", {Engine->ScreenWidth()/2-50, Engine->ScreenHeight()/2-60}, {100.0f, 50.0f}); 

  //MainMenuText->bHasBorder = true;
  bIsInitialized = true;
}

