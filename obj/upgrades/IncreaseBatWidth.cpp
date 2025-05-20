#include "IncreaseBatWidth.h"
#include "engine/engine.h"
#include "obj/Bat.h"

IncreaseBatWidthUpgrade::IncreaseBatWidthUpgrade(float InUpgradeLifespan,
                                                 float InNewBatWidth)
    : BaseUpgrade(InUpgradeLifespan)
{
  NewBatWidth = InNewBatWidth;
}

void IncreaseBatWidthUpgrade::ApplyUpgrade(Engine* Engine)
{
  std::vector<std::shared_ptr<BaseObject>> BatObjects =
      Engine->GetGameObjectOfType<Bat>();
  if (BatObjects.size() <= 0)
  {
    return;
  }

  std::shared_ptr<Bat> UserBat = std::static_pointer_cast<Bat>(BatObjects[0]);

  OldBatWidth = UserBat->BatWidth;
  UserBat->BatWidth = NewBatWidth;
}

void IncreaseBatWidthUpgrade::RemoveUpgrade(Engine* Engine)
{
  std::vector<std::shared_ptr<BaseObject>> BatObjects =
      Engine->GetGameObjectOfType<Bat>();
  if (BatObjects.size() <= 0)
  {
    return;
  }

  std::shared_ptr<Bat> UserBat = std::static_pointer_cast<Bat>(BatObjects[0]);

  UserBat->BatWidth = OldBatWidth;
}
