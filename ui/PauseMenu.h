#include "../lib/olcPixelGameEngine.h"
#include "../lib/olcPGEX_QuickGUI.h"

class Engine;

class PauseMenu
{
public:
  olc::QuickGUI::Button* ResumeButton;
  olc::QuickGUI::Label* PauseLabel;

  void Initialize(Engine* Engine, olc::QuickGUI::Manager& GuiManager);
  bool bIsInitialized = false;
};
