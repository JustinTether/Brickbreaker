#include "../engine/engine.h"
#include "Ball.h"
#include "BaseBrick.h"
#include "BaseObject.h"
#include "Bat.h"
#include "engine/AudioManager.h"
#include "engine/GameState.h"
Ball::Ball(Engine* Engine)
{
  // Set initial ball position to the middle of the screen-ish
  BallRadius = 5;
  BallColour = olc::BLUE;
  BallSpeed = 3.0f;
  float Angle = -0.4f;
  float BallAngle = -1.25f;
  BallVelocity = {static_cast<float>(BallSpeed * cos(BallAngle)),
                  static_cast<float>(BallSpeed * sin(BallAngle))};
  BallPosition = olc::vf2d(12.5f, 15.5f);
  HitSound = AudioManager::Get()->RegisterNewSound("assets/sounds/hit.wav");
}

void Ball::Draw(Engine* Engine)
{
  Engine->FillCircle(BallPosition * Engine->TileSize, BallRadius, BallColour);
}

void Ball::Update(Engine* Engine, float DeltaTime)
{
  BallPosition += BallVelocity * BallSpeed * DeltaTime;
  // std::cout << "Ball Position: " << BallPosition * Engine->TileSize <<
  // "\n"; std::cout << "Bat Position: " << Engine->UserBat->BatPosition <<
  // "\n";

  bool bHasHitTile = false;
  bHasHitTile |= TestCollisionPoint(olc::vf2d(0, -1), Engine);
  bHasHitTile |= TestCollisionPoint(olc::vf2d(0, +1), Engine);
  bHasHitTile |= TestCollisionPoint(olc::vf2d(-1, 0), Engine);
  bHasHitTile |= TestCollisionPoint(olc::vf2d(+1, 0), Engine);

  olc::vf2d ModifiedBallPosition = BallPosition * Engine->TileSize;

  std::vector<std::shared_ptr<BaseObject>> BatObjects =
      Engine->GetGameObjectOfType<Bat>();
  if (BatObjects.size() <= 0)
  {
    return;
  }

  std::shared_ptr<Bat> UserBat = std::static_pointer_cast<Bat>(BatObjects[0]);
  float BatPosition = UserBat->BatPosition;

  // Check if modified ball position is at the same y level as the paddle
  if (ModifiedBallPosition.y >=
      ((Engine->GameState->MapHeight * Engine->TileSize.y) - 20) -
          UserBat->BatHeight)
  {
    // Check if the modified position is at the same x offset
    if (ModifiedBallPosition.x > BatPosition &&
        ModifiedBallPosition.x < BatPosition + UserBat->BatWidth)
    {
      BallVelocity.y *= -1.0;

      // Change X based on where the ball hit
      // Grab the 'HitPosition' of the ball, 0 for far left edge, 1 for
      // far right edge
      float HitPosition =
          ((BallPosition.x * Engine->TileSize.x) - BatPosition) /
          UserBat->BatWidth;

      // Create an angle multiplier based off of this position -0.5 so
      // that the modified position is between -0.5 and +0.5, POW'd
      float AngleMultiplier = pow((HitPosition - 0.5f) * 2.0f, 3);

      // Calculate a new angle in Radians so that the sin/cos functions
      // work
      float MaxAngle = 60.0f;
      float AngleRadians = (MaxAngle * AngleMultiplier) * (M_PI / 180.0f);

      float Speed = sqrt(BallVelocity.x * BallVelocity.x +
                         BallVelocity.y * BallVelocity.y);
      BallVelocity.x = Speed * sin(AngleRadians);
      BallVelocity.y = -Speed * cos(AngleRadians);
    }
  }

  // Check if ball has gone off screen
  if (ModifiedBallPosition.y >
      Engine->GameState->MapHeight * Engine->TileSize.y)
  {
    std::cout << "Ball outside of play, resetting\n";
    ResetBall(Engine);
  }
}

void Ball::ResetBall(Engine* Engine)
{
  // Set a random angle/velocity for the ball and reset to center of screen
  // float BallAngle = (float(rand()) / (float(RAND_MAX) * 2.0f) * 3.14169f);

  if (bIsExtraBall)
  {
    // TODO: This feels a bit jank, I dunno if the ball should remove itself
    // like this
    bShouldBeGCd = true;
    // Engine->RemoveGameObject(std::shared_ptr<BaseObject>(this));
    return;
  }

  Engine->GameState->SetNumBallsRemaining(
      Engine->GameState->GetNumBallsRemaining() - 1);
  float BallAngle = -1.25f;

  BallVelocity = {static_cast<float>(BallSpeed * cos(BallAngle)),
                  static_cast<float>(BallSpeed * sin(BallAngle))};
  BallPosition = olc::vf2d(12.5f, 15.5f);
}

bool Ball::TestCollisionPoint(olc::vf2d point, Engine* Engine)
{
  olc::vf2d TileBallRadialDims = {BallRadius / Engine->TileSize.x,
                                  BallRadius / Engine->TileSize.y};
  olc::vf2d PotentialBallPos =
      BallPosition + BallVelocity * Engine->GetElapsedTime();

  olc::vi2d TestPoint = PotentialBallPos + TileBallRadialDims * point;

  std::vector<std::shared_ptr<BaseObject>> Bricks =
      Engine->GetGameObjectOfType<BaseBrick>();
  if (Bricks.size() <= 0)
  {
    return false;
  }

  std::shared_ptr<BaseBrick> Brick;
  for (std::shared_ptr<BaseObject> Obj : Bricks)
  {
    std::shared_ptr<BaseBrick> BrickObj =
        std::static_pointer_cast<BaseBrick>(Obj);
    if (!BrickObj)
    {
      continue;
    }

    if (BrickObj->XPosition == TestPoint.x &&
        BrickObj->YPosition == TestPoint.y)
      Brick = BrickObj;
  }

  if (!Brick)
  {
    return false;
  }

  if (Brick->bIsAir)
    return false;

  // Ball has collided with a tile
  bool bTileHit = !Brick->bIsAir && !Brick->bIsWall;
  if (bTileHit)
    Brick->OnCollide();

  if (bTileHit)
  {
    AudioManager::Get()->PlaySound(HitSound);
  }

  // Collision response
  if (point.x == 0.0f)
  {
    BallVelocity.y *= -1.0f;
  }

  if (point.y == 0.0f)
  {
    BallVelocity.x *= -1.0f;
  }

  return bTileHit;
}
