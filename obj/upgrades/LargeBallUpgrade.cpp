#include "LargeBallUpgrade.h"
#include "engine/engine.h"
#include "obj/Ball.h"

LargeBallUpgrade::LargeBallUpgrade(float InUpgradeLifespan, float InNewBallSize)
    : BaseUpgrade(InUpgradeLifespan)
{
  NewBallSize = InNewBallSize;
  UpgradeLifespan = InUpgradeLifespan;
}

void LargeBallUpgrade::ApplyUpgrade(Engine* Engine)
{
  std::vector<std::shared_ptr<BaseObject>> BallObjects =
      Engine->GetGameObjectOfType<Ball>();

  if (BallObjects.size() <= 0)
  {
    return;
  }

  std::shared_ptr<Ball> UserBall;
  for (std::shared_ptr<BaseObject> Obj : BallObjects)
  {
    std::shared_ptr<Ball> BallObj = std::dynamic_pointer_cast<Ball>(Obj);
    if (!BallObj->bIsExtraBall)
      UserBall = BallObj;
  }

  OldBallSize = UserBall->OriginalBallRadius;
  UserBall->BallRadius = UserBall->BallRadius + NewBallSize;
  BaseUpgrade::ApplyUpgrade(Engine);
}

void LargeBallUpgrade::RemoveUpgrade(Engine* Engine)
{
  std::vector<std::shared_ptr<BaseObject>> BallObjects =
      Engine->GetGameObjectOfType<Ball>();

  if (BallObjects.size() <= 0)
  {
    return;
  }

  std::shared_ptr<Ball> UserBall;
  for (std::shared_ptr<BaseObject> Obj : BallObjects)
  {
    std::shared_ptr<Ball> BallObj = std::dynamic_pointer_cast<Ball>(Obj);
    if (!BallObj->bIsExtraBall)
      UserBall = BallObj;
  }

  UserBall->BallRadius = UserBall->OriginalBallRadius;
  bShouldBeGCd = true;
}