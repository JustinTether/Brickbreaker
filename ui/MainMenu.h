#pragma once

#include "../lib/olcPixelGameEngine.h"
class Engine;
class ClayPGERenderer;

class MainMenuGUI
{
public:
  // ID reference for the click sound
  int ClickSound;
  ClayPGERenderer* ClayRenderer;
  float MainMenuButtonWidth = 100.f;
  float MainMenuButtonHeight = 16.0f;
  
  bool bIsInitialized = false;
        
  void Initialize(Engine* EngineInstance);
  void Draw(Engine* Engine);

  bool bDebugClay;
  bool bIsStartButtonPressed;

};
