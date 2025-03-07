#include "BaseObject.h"
#include "Ball.h"
#include "../engine/engine.h"
Ball::Ball(Engine* Engine)
{
    // Set initial ball position to the middle of the screen-ish
    BallRadius = 5;
    BallColour = olc::BLUE;
    BallSpeed = 3.0f;
    float Angle = -0.4f;
    BallVelocity = { static_cast<float>(cos(Angle)), static_cast<float>(sin(Angle)) };
    BallPosition = olc::vf2d(12.5f, 15.5f);
    HitSound = Engine->AudioManager.LoadSound("../assets/sounds/hit.wav");
    ResetBall(Engine);
}


void Ball::Draw(Engine* Engine) 
{
  Engine->FillCircle(BallPosition * Engine->TileSize, BallRadius, BallColour);
}

void Ball::Update(Engine* Engine, float DeltaTime) 
{
    BallPosition += BallVelocity * BallSpeed * DeltaTime;
    //std::cout << "Ball Position: " << BallPosition * Engine->TileSize << "\n";
    //std::cout << "Bat Position: " << Engine->UserBat->BatPosition << "\n";

    bool bHasHitTile = false;
    bHasHitTile |= TestCollisionPoint(olc::vf2d(0, -1), Engine);
    bHasHitTile |= TestCollisionPoint(olc::vf2d(0, +1), Engine);
    bHasHitTile |= TestCollisionPoint(olc::vf2d(-1, 0), Engine);
    bHasHitTile |= TestCollisionPoint(olc::vf2d(+1, 0), Engine);	
    
    olc::vf2d ModifiedBallPosition = BallPosition * Engine->TileSize;
    float BatPosition = Engine->UserBat->BatPosition;

    // Check if modified ball position is at the same y level as the paddle
    if (ModifiedBallPosition.y >= (Engine->ScreenHeight()-20) - Engine->UserBat->BatHeight)
    {
      // Check if the modified position is at the same x offset
      if (ModifiedBallPosition.x > BatPosition && ModifiedBallPosition.x < BatPosition + Engine->UserBat->BatWidth)
      {
        BallVelocity.y *= -1.0;
      }
    }

    // Check if ball has gone off screen
    if (ModifiedBallPosition.y > Engine->ScreenHeight())
    {
        std::cout << "Ball outside of play, resetting\n";
        ResetBall(Engine);
    }
}

void Ball::ResetBall(olc::PixelGameEngine* Engine)
{
    // Set a random angle/velocity for the ball and reset to center of screen
    //float BallAngle = (float(rand()) / (float(RAND_MAX) * 2.0f) * 3.14169f);
    float BallAngle = -1.25f;

    BallVelocity = {static_cast<float>(BallSpeed * cos(BallAngle)), static_cast<float>(BallSpeed * sin(BallAngle))};
    BallPosition = olc::vf2d(12.5f, 15.5f);
}

bool Ball::TestCollisionPoint(olc::vf2d point, Engine* Engine)
{
    olc::vf2d TileBallRadialDims = { BallRadius / Engine->TileSize.x, BallRadius / Engine->TileSize.y };
    olc::vf2d PotentialBallPos = BallPosition + BallVelocity * Engine->GetElapsedTime();

    olc::vi2d TestPoint = PotentialBallPos + TileBallRadialDims * point;
    auto& tile = Engine->Tiles[TestPoint.y * Engine->MapWidth + TestPoint.x];
    if (tile == 0)
    {
        // Do Nothing, no collision
        return false;
    }
    else
    {
        // Ball has collided with a tile
        bool bTileHit = tile < 10;
        if (bTileHit) tile--;
               
        if(bTileHit)
        {
          Engine->AudioManager.Play(HitSound);
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

}
