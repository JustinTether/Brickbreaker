#pragma once
#include "lib/olcPGEX_QuickGUI.h"

class OptionsMenu
{
public:
  OptionsMenu();
  olc::QuickGUI::Slider* MusicVolumeSlider;
  olc::QuickGUI::Manager GUIManager;
};