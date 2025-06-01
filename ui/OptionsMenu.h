#pragma once
#include "engine/Clay_Renderer_PGE.h"
#include "engine/GameState.h"
#include "lib/olcPGEX_QuickGUI.h"

class OptionsMenu
{
public:
  OptionsMenu();
  olc::QuickGUI::Slider* MusicVolumeSlider;
  olc::QuickGUI::Slider* EffectsVolumeSlider;
  olc::QuickGUI::Manager GUIManager;

  EGameState LastGameState;
  void Draw();
  void Initialize();
  bool bIsInitialized = false;
  bool bIsBackButtonPressed = false;

private:
  Arena FrameArena;
  float MusicVolume;
  float PreviousMusicVolume;
  float PreviousEffectsVolume;
  float EffectsVolume;
};