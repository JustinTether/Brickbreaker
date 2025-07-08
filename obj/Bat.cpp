#pragma once
#include "Bat.h"
#include "engine/GameState.h"
#include "engine/engine.h"

Bat::Bat(olc::PixelGameEngine* Engine)
{
  BatPosition = olc::vi2d(
      20.f,
      (Engine::Get()->GameState->MapHeight * Engine::Get()->TileSize.y) - 20);

  BatWidth = 40.f;
  BatSpeed = 250.0f;
  BatHeight = 5.0f;
  OriginalBatSpeed = BatSpeed;
  OriginalBatWidth = BatWidth;
}

void Bat::Draw(Engine* EngineInstance)
{
  EngineInstance->FillRect(BatPosition.x, BatPosition.y, int(BatWidth),
                           int(BatHeight), olc::YELLOW);
}

void Bat::Update(Engine* EngineInstance, float DeltaTime)
{
  if (EngineInstance->GetKey(olc::Key::LEFT).bHeld ||
      EngineInstance->GetMouse(0).bHeld &&
          EngineInstance->GetMousePos().x <= EngineInstance->ScreenWidth() / 2)
    BatPosition.x -= BatSpeed * DeltaTime;

  if (EngineInstance->GetKey(olc::Key::RIGHT).bHeld ||
      EngineInstance->GetMouse(0).bHeld &&
          EngineInstance->GetMousePos().x >= EngineInstance->ScreenWidth() / 2)
    BatPosition.x += BatSpeed * DeltaTime;

  // Constrain bat to the edges of the screen
  if (BatPosition.x < 12.0f)
  {
    BatPosition.x = 12.0f;
  }

  if (BatPosition.x + BatWidth >
      float((EngineInstance->GameState->MapWidth * EngineInstance->TileSize.x) -
            EngineInstance->TileSize.x))
  {
    BatPosition.x = float(EngineInstance->ScreenWidth() -
                          EngineInstance->TileSize.x - BatWidth);
  }
}
