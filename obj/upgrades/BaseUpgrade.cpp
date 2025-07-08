#include "BaseUpgrade.h"
#include "engine/GameState.h"
#include "engine/engine.h"
#include "obj/Bat.h"

BaseUpgrade::BaseUpgrade(float InUpgradeLifespan)
{
  InitialLifespan = InUpgradeLifespan;
  UpgradeLifespan = InitialLifespan;
  bInitialized = false;
}

void BaseUpgrade::Initialize(Engine* Engine) { bInitialized = true; }

void BaseUpgrade::ApplyUpgrade(Engine* Engine) { bIsApplied = true; }

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

  if (bIsApplied)
  {
    UpgradeLifespan -= fElapsedTime;
    std::cout << "New Lifespan: " << UpgradeLifespan << "\n";

    if (UpgradeLifespan <= 0.0f)
    {
      std::cout << "Removing upgrade, lifespan: " << UpgradeLifespan << "\n";
      RemoveUpgrade(Engine);
    }
  }

  if (!bIsApplied)
  {
    // Move the upgrade downwards
    PosY += FallSpeed * fElapsedTime;

    // Check for a collision with the bat
    std::vector<std::shared_ptr<BaseObject>> BatObjects =
        Engine->GetGameObjectOfType<Bat>();

    if (BatObjects.size() < 1)
    {
      return;
    }

    std::shared_ptr<Bat> UserBat =
        std::dynamic_pointer_cast<Bat>(BatObjects[0]);
    if (!UserBat)
    {
      return;
    }

    if (PosY >= UserBat->BatPosition.y + UserBat->BatHeight &&
        PosX >= UserBat->BatPosition.x &&
        PosX <= UserBat->BatPosition.x + UserBat->BatWidth)
    {

      // TOOD: Apply the upgrade if we successfully hit the bat
      ApplyUpgrade(Engine);
    }
  }

  if (PosY >= Engine::Get()->GameState->MapHeight && !bIsApplied)
    RemoveUpgrade(Engine);
}

void BaseUpgrade::Draw(Engine* Engine)
{

  // Only draw the upgrade if it's not applied
  if (!bIsApplied)
    Engine->DrawPartialSprite(
        olc::vi2d(PosX, PosY) * Engine->TileSize, Engine->TileSheet.get(),
        olc::vi2d(TileOffset, 0) * Engine->TileSize, Engine->TileSize);
}

void BaseUpgrade::Reset()
{
  UpgradeLifespan = InitialLifespan;
  ApplyUpgrade(Engine::Get());
}
