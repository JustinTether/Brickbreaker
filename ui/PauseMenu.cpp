#include "PauseMenu.h"
#include "../engine/engine.h"
#include "olcPGEX_QuickGUI.h"

void PauseMenu::Initialize(Engine* Engine, olc::QuickGUI::Manager& GuiManager)
{
  PauseLabel = new olc::QuickGUI::Label(GuiManager, "Paused", {static_cast<float>(Engine->ScreenWidth()/2), static_cast<float>(Engine->ScreenHeight()/2)}, {10.0f, 10.0f});
  ResumeButton = new olc::QuickGUI::Button(GuiManager, "Resume",
    {static_cast<float>((Engine->ScreenWidth()/2)-50), static_cast<float>((Engine->ScreenHeight()/2)+40)},
    {100.0f, 16.0f});

  bIsInitialized = true; 
}
