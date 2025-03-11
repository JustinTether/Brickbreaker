//
// Created by justin on 2/11/25.
//
#pragma once
#ifndef BALL_H
#define BALL_H
#include "BaseObject.h"
#include "../lib/olcPixelGameEngine.h"

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

};


#endif //BALL_H
