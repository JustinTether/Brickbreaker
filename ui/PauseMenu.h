#include "../lib/olcPixelGameEngine.h"
#include "engine/engine.h"

class ClayPGERenderer;
class Engine;

class PauseMenu
{
public:
  ClayPGERenderer* ClayRenderer;
  void Initialize(Engine* Engine); 
  void Draw(Engine* Engine);
  bool bIsInitialized = false;
  bool bIsResumeButtonClicked = false;
};
