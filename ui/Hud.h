#pragma once
class Engine;

class Hud 
{
public:
  void Initialize(Engine* Engine);
  void Draw(Engine* Engine);
  bool bIsInitialized = false;
  bool bDebugClay = false;
};
