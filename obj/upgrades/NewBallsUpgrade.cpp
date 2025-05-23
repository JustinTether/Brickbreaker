#include "NewBallsUpgrade.h"
#include "engine/engine.h"
#include "obj/Ball.h"

NewBallsUpgrade::NewBallsUpgrade(float InUpgradeLifespan, int InNumNewBalls)
    : BaseUpgrade(InUpgradeLifespan)
{
  NumberOfBalls = InNumNewBalls;
}

void NewBallsUpgrade::ApplyUpgrade(Engine* Engine)
{
  for (int i = 0; i < NumberOfBalls; i++)
  {
    std::shared_ptr<Ball> NewBall = std::make_shared<Ball>(Engine);
    NewBall->bIsExtraBall = true;
    NewBall->BallColour = olc::YELLOW;

    ActiveUpgrades.push_back(std::shared_ptr<BaseObject>(
        std::static_pointer_cast<BaseObject>(NewBall)));
  }

  for (auto Ball : ActiveUpgrades)
  {
    Engine->AddNewGameObject(Ball);
  }
}

void NewBallsUpgrade::RemoveUpgrade(Engine* Engine)
{
  // Balls should handle themselves, so we should just clear our vector so we're
  // not dangling in memory
  ActiveUpgrades.clear();
}
