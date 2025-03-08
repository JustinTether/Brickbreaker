#include "BaseBrick.h"
#include "../engine/engine.h"

BaseBrick::BaseBrick()
{
  // Defaults
  bIsAir = false;
  bIsWall = false;
  MaxHits = 0;
  TileOffset = 0;
  CurrentHits = 0;

}

void BaseBrick::Draw(Engine* Engine)
{
  // Draw the tile at the specified tile coordinates
}


void BaseBrick::Update(Engine* Engine, float DeltaTime)
{
  // performed on-tick operations, if they're needed
}

void BaseBrick::OnCollide()
{
  if (bIsAir || bIsWall)
    return;

  MaxHits--;

  if (MaxHits == 0)
    bIsAir = true;
}
