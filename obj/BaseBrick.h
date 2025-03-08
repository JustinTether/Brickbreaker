#pragma once
#include "BaseObject.h"

class BaseBrick : public BaseObject
{
public:
  BaseBrick();

  float XPosition;
  float YPosition;
  int MaxHits;
  int CurrentHits;

  // Whether this is a barrier and shouldn't ever take collision damage
  bool bIsWall;

  // Whether this is air and should not have a sprite ID or be rendered in any way
  bool bIsAir;
  
  // Maybe there's a better way to do this? But, I think that we need to define a static offset for the brick in the spritesheet
  float TileOffset;
  virtual void Draw(Engine* Engine) override;
  virtual void Update(Engine* Engine, float DeltaTime) override;
  void OnCollide();
};

