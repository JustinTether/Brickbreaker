#pragma once
#include "Bat.h"


Bat::Bat(olc::PixelGameEngine* Engine)
{
  BatPosition = 20.f;
  BatWidth = 40.f;
  BatSpeed = 250.0f;
  BatHeight = 5.0f;
}

void Bat::Draw(Engine* EngineInstance) 
{
  EngineInstance->FillRect(int(BatPosition), EngineInstance->ScreenHeight()-20, int(BatWidth), int(BatHeight), olc::YELLOW);
}

void Bat::Update(Engine* EngineInstance, float DeltaTime) 
{  
  if (EngineInstance->GetKey(olc::Key::LEFT).bHeld) BatPosition -= BatSpeed * DeltaTime;
  if (EngineInstance->GetKey(olc::Key::RIGHT).bHeld) BatPosition += BatSpeed * DeltaTime;

  // Constrain bat to the edges of the screen
  if (BatPosition < 12.0f) BatPosition = 12.0f;
  if(BatPosition + BatWidth > float(EngineInstance->ScreenWidth() - EngineInstance->TileSize.x)) BatPosition = float(EngineInstance->ScreenWidth() - EngineInstance->TileSize.x - BatWidth);


}

