#pragma once
#include "olcPGEX_QuickGUI.h"
class Engine;

class Hud 
{
public:
  void Initialize(Engine* Engine);
  bool bIsInitialized = false;


  olc::QuickGUI::Manager HudManager;
  olc::QuickGUI::Label* BallsRemainingLabel;
  olc::QuickGUI::Label* BallsRemainingNumber;
  olc::QuickGUI::ListBox* PowerUpsListBox;
};
