#include "../lib/olcPixelGameEngine.h"
#include "engine/engine.h"

class Engine;

class PauseMenu
{
public:
  int ClickSound;
  void Initialize(Engine* Engine);
  void Draw(Engine* Engine);
  bool bIsInitialized = false;
  bool bIsResumeButtonClicked = false;
};
