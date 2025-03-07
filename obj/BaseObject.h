//
// Created by justin on 2/11/25.
//
#pragma once
#ifndef BASEOBJECT_H
#define BASEOBJECT_H
#include "../lib/olcPixelGameEngine.h"
#include "../engine/engine.h"

class BaseObject
{

protected:
public:
    BaseObject();
    virtual void Draw(Engine* Engine);
    virtual void Update(Engine* Engine, float DeltaTime);

    void Tick(Engine* Engine, float DeltaTime);
};


#endif //BASEOBJECT_H


