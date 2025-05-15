#include "IncreaseBatWidth.h"
#include "engine/engine.h"
#include "obj/Bat.h"

IncreaseBatWidthUpgrade::IncreaseBatWidthUpgrade(float InUpgradeLifespan, float InNewBatWidth) : BaseUpgrade(InUpgradeLifespan)
{
  NewBatWidth = InNewBatWidth;
}

void IncreaseBatWidthUpgrade::ApplyUpgrade(Engine* Engine)
{
  Bat* UserBat = Engine->GetGameObjectOfType<Bat>();
  if (!UserBat)
  {
    return;
  }

  OldBatWidth = UserBat->BatWidth;
  UserBat->BatWidth = NewBatWidth;
}

void IncreaseBatWidthUpgrade::RemoveUpgrade(Engine* Engine)
{
  Bat* UserBat = Engine->GetGameObjectOfType<Bat>();
  if (!UserBat)
  {
    return;
  }

  UserBat->BatWidth = OldBatWidth;
}
