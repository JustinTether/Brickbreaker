#include "BaseUpgrade.h"

class Engine;

class IncreaseBatWidthUpgrade : public BaseUpgrade
{
public:
  IncreaseBatWidthUpgrade(float InUpgradeLifespan, float InNewBatWidth);
private:
  float NewBatWidth;
  float OldBatWidth;
  virtual void ApplyUpgrade(Engine* Engine) override;
  virtual void RemoveUpgrade(Engine* Engine) override;

};
