#pragma once
#include "../lib/olcPixelGameEngine.h"
#include "BaseObject.h"

class Engine;

class Bat : public BaseObject
{
public:
  float BatPosition;
  float BatWidth;
  float BatSpeed;
  float BatHeight;
  float OriginalBatWidth;
  float OriginalBatSpeed;

  Bat(olc::PixelGameEngine* Engine);
  virtual void Draw(Engine* EngineInstance) override;
  virtual void Update(Engine* EngineInstance, float DeltaTime) override;
};
