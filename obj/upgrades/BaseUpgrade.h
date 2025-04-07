#pragma once
#include "BaseObject.h"

class Engine;

class BaseUpgrade : public BaseObject
{
public:
  virtual void ApplyUpgrade(Engine* Engine);
  void Tick(Engine* Engine);
  float UpgradeLifespan;

private:
  float UpgradeAppliedTime;
  float TimeRemaining;
  float StartTime;
  virtual void RemoveUpgrade(Engine* Engine);
  void Initialize(Engine* Engine);
  bool bInitialized = false;

};
