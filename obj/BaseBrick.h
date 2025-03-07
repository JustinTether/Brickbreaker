#pragma once
#include "BaseObject.h"

class Engine;

class BaseBrick : public BaseObject
{
public:
  float XPosition;
  float YPosition;
  int MaxHits;
  int CurrentHits;
  
  // Maybe there's a better way to do this? But, I think that we need to define a static offset for the brick in the spritesheet
  float TileOffset;
  virtual void Draw(Engine* Engine) override;
  virtual void Update(Engine* Engine, float DeltaTime) override;

};

