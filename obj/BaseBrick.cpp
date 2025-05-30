#include "BaseBrick.h"
#include "../engine/engine.h"
#include "engine/GameState.h"

BaseBrick::BaseBrick()
{
  // Defaults
  bIsAir = false;
  bIsWall = false;
  bIsUpgrade = false;
  MaxHits = 0;
  TileOffset = 0;
  CurrentHits = 0;
}

void BaseBrick::Draw(Engine* Engine)
{
  // Draw the tile at the specified tile coordinates
  if (bIsAir)
    return;

  Engine->SetPixelMode(
      olc::Pixel::MASK); // Dont draw pixels which have any transparency

  if (bIsUpgrade)
  {
    Engine->DrawPartialSprite(
        olc::vi2d(XPosition, YPosition) * Engine->TileSize,
        Engine->TileSheet.get(), olc::vi2d(4, 0) * Engine->TileSize,
        Engine->TileSize);
  }
  else
  {
    Engine->DrawPartialSprite(
        olc::vi2d(XPosition, YPosition) * Engine->TileSize,
        Engine->TileSheet.get(), olc::vi2d(MaxHits, 0) * Engine->TileSize,
        Engine->TileSize);
  }

  Engine->SetPixelMode(
      olc::Pixel::NORMAL); // Dont draw pixels which have any transparency
}

void BaseBrick::Update(Engine* Engine, float DeltaTime)
{
  // performed on-tick operations, if they're needed
}

void BaseBrick::OnCollide()
{
  if (bIsAir || bIsWall)
    return;

  if (bIsUpgrade)
  {
    Engine::Get()->GameState->ApplyRandomUpgrade();
    bIsUpgrade = false;
    bIsAir = true;
    return;
  }

  MaxHits--;

  if (MaxHits == 0)
  {

    // Decrement bricks count
    Engine::Get()->GameState->SetNumBricksRemaining(
        Engine::Get()->GameState->GetNumBricksRemaining() - 1);

    // Determine if we're supposed to be an upgrade block, there should be some
    // chance for this to occur
    // This is just a 25% chance, but should honestly be a more sophisticated
    // approach
    if (rand() % 100 + 0 >= 75)
    {
      bIsUpgrade = true;
      return;
    }

    bIsAir = true;
  }
}
