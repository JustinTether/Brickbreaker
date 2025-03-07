#pragma once
#include "BaseObject.h"

BaseObject::BaseObject()
{

}

void BaseObject::Draw(Engine* Engine)
{

}

void BaseObject::Update(Engine* Engine, float DeltaTime)
{

}

void BaseObject::Tick(Engine* Engine, float DeltaTime)
{
        Update(Engine, DeltaTime);
        Draw(Engine);
}
