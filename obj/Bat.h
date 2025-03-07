#pragma once
#include "BaseObject.h"
#include "../lib/olcPixelGameEngine.h"

class Bat : public BaseObject
{
  public:
    float BatPosition;
    float BatWidth;
    float BatSpeed;
    float BatHeight;
    
    Bat(olc::PixelGameEngine* Engine);
    virtual void Draw(Engine* EngineInstance) override;
    virtual void Update(Engine* EngineInstance, float DeltaTime) override;
    
};
