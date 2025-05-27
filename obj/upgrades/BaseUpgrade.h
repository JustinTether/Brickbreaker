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

private:
  float UpgradeAppliedTime;
  float StartTime;
  virtual void RemoveUpgrade(Engine* Engine);
  virtual void ApplyUpgrade(Engine* Engine);
  void Initialize(Engine* Engine);
  bool bInitialized = false;
  float InitialLifespan;
};
