#pragma once

#include "lib/olcPixelGameEngine.h"
class ClayPGERenderer;
class Engine;

class GameOverGUI
{
public:
  // ID reference for the click sound
  int ClickSound;

  bool bIsInitialized = false;

  void Initialize(Engine* EngineInstance);
  void Draw(Engine* Engine);

  bool bDebugClay;
  bool bIsNewGameButtonPressed = false;
  bool bIsMainMenuButtonPressed = false;
};
