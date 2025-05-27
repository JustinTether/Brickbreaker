#include "BaseUpgrade.h"
#include "engine/engine.h"

BaseUpgrade::BaseUpgrade(float InUpgradeLifespan)
{
  InitialLifespan = InUpgradeLifespan;
  UpgradeLifespan = InitialLifespan;
  bInitialized = false;
}

void BaseUpgrade::Initialize(Engine* Engine)
{
  ApplyUpgrade(Engine);
  bInitialized = true;
}

void BaseUpgrade::ApplyUpgrade(Engine* Engine) {}

void BaseUpgrade::RemoveUpgrade(Engine* Engine) { bShouldBeGCd = true; }

void BaseUpgrade::Update(Engine* Engine, float fElapsedTime)
{
  if (UpgradeLifespan <= 0.0f)
  {
    return;
  }

  if (!bInitialized)
  {
    Initialize(Engine);
  }

  UpgradeLifespan -= fElapsedTime;
  std::cout << "New Lifespan: " << UpgradeLifespan << "\n";

  if (UpgradeLifespan <= 0.0f)
  {
    std::cout << "Removing upgrade, lifespan: " << UpgradeLifespan << "\n";
    RemoveUpgrade(Engine);
  }
}

void BaseUpgrade::Reset()
{
  UpgradeLifespan = InitialLifespan;
  ApplyUpgrade(Engine::Get());
}
