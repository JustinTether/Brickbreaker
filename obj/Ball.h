#pragma once
#ifndef BALL_H
#define BALL_H
#include "../lib/olcPixelGameEngine.h"
#include "BaseObject.h"

class Engine;

class Ball : public BaseObject
{
public:
  Ball(Engine* Engine);

  void Draw(Engine* EngineInstance) override;
  void Update(Engine* EngineInstance, float DeltaTime) override;

  float BallRadius;
  olc::vf2d BallPosition;
  olc::vf2d BallVelocity;
  olc::Pixel BallColour;
  float BallSpeed;

  void ResetBall(Engine* Engine);
  bool TestCollisionPoint(olc::vf2d Point, Engine* EngineInstance);

  // Sound IDs
  int HitSound;
  bool bIsExtraBall = false;

private:
};

#endif // BALL_H
