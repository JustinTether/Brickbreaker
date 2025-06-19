#include "BaseUpgrade.h"
class Engine;

class LargeBallUpgrade : public BaseUpgrade
{
public:
  LargeBallUpgrade(float InUpgradeLifespan, float InNewBallSize);

private:
  virtual void ApplyUpgrade(Engine* Engine) override;
  virtual void RemoveUpgrade(Engine* Engine) override;
  float NewBallSize;
  float OldBallSize;
};