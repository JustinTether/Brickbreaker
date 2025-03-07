#pragma once

#include "../lib/olcPixelGameEngine.h"
#include "../lib/olcPGEX_QuickGUI.h"

class Engine;

class MainMenuGUI
{
public:
  // GUI Controls pointers
  olc::QuickGUI::Button* MainMenuStartButton = nullptr;
  olc::QuickGUI::Label* MainMenuText = nullptr;

  // ID reference for the click sound
  int ClickSound;

  float MainMenuButtonWidth = 100.f;
  float MainMenuButtonHeight = 16.0f;
  olc::QuickGUI::Manager MainMenuManager;

  bool bIsInitialized = false;
        
  void Initialize(Engine* EngineInstance);  

};
