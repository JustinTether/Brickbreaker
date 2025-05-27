#pragma once
#include "obj/upgrades/BaseUpgrade.h"
#include <vector>
class Engine;

class NewBallsUpgrade : public BaseUpgrade
{

public:
  NewBallsUpgrade(float InUpgradeLifespan, int InNumNewBalls);

private:
  int NumberOfBalls;
  std::vector<std::shared_ptr<BaseObject>> ActiveUpgrades;
  virtual void ApplyUpgrade(Engine* Engine);
  virtual void RemoveUpgrade(Engine* Engine);
};
