#pragma once
#include "BaseObject.h"

class Engine;

class BaseUpgrade : public BaseObject
{
public:
  BaseUpgrade(float UpgradeLifespan);
  virtual void Update(Engine* Engine, float fElapsedTime) override;
  float TimeRemaining;
  float UpgradeLifespan;
  virtual void Reset();
  bool bIsApplied = false;
  float PosX;
  float PosY;
  virtual void ApplyUpgrade(Engine* Engine);

private:
  virtual void Draw(Engine* Engine) override;
  float UpgradeAppliedTime;
  float StartTime;
  virtual void RemoveUpgrade(Engine* Engine);
  void Initialize(Engine* Engine);
  bool bInitialized = false;
  float InitialLifespan;
  int TileOffset = 4;

  float FallSpeed = 0.5;
};
