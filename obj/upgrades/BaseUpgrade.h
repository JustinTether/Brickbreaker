#pragma once
#include "BaseObject.h"

class Engine;

class BaseUpgrade : public BaseObject
{
public:
  BaseUpgrade(float UpgradeLifespan);
  virtual void Update(Engine* Engine, float fElapsedTime) override;
  float TimeRemaining;

private:
  float UpgradeAppliedTime;
  float StartTime;
  virtual void RemoveUpgrade(Engine* Engine);
  virtual void ApplyUpgrade(Engine* Engine);
  float UpgradeLifespan;
  void Initialize(Engine* Engine);
  bool bInitialized = false;
};
