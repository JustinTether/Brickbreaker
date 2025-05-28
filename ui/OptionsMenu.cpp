#include "OptionsMenu.h"

OptionsMenu::OptionsMenu()
{
  MusicVolumeSlider = new olc::QuickGUI::Slider(GUIManager, olc::vf2d(0, 0),
                                                olc::vf2d(0, 0), 0, 1.0f, 1.0f);
}
