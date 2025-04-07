#include "BaseUpgrade.h"
#include "engine/engine.h"

void BaseUpgrade::Initialize(Engine* Engine)
{
  ApplyUpgrade(Engine);
  bInitialized = true;
}

void BaseUpgrade::ApplyUpgrade(Engine* Engine)
{
  
}

void BaseUpgrade::RemoveUpgrade(Engine* Engine)
{

}

void BaseUpgrade::Tick(Engine* Engine)
{

  if(!bInitialized)
  {
    Initialize(Engine);
  }

  UpgradeLifespan -= Engine->GetElapsedTime();

  if(UpgradeLifespan <= 0.0f)
  {
    RemoveUpgrade(Engine);
  }

}



