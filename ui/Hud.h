#pragma once
#include <string>
#include <vector>
class Engine;

class Hud
{
public:
  void Initialize(Engine* Engine);
  void Draw(Engine* Engine);
  bool bIsInitialized = false;
  bool bDebugClay = false;

private:
  std::vector<std::string> UIStrings;
};
