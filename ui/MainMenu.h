#pragma once

#include "../lib/olcPixelGameEngine.h"
class Engine;
class ClayPGERenderer;

class MainMenuGUI
{
public:
  // ID reference for the click sound
  int ClickSound;
  float MainMenuButtonWidth = 100.f;
  float MainMenuButtonHeight = 16.0f;

  bool bIsInitialized = false;

  void Initialize(Engine* Engine);
  void Draw(Engine* Engine);

  bool bDebugClay;
  bool bIsStartButtonPressed;
  bool bIsOptionsButtonPressed;
  bool bIsQuitButtonPressed;
};
