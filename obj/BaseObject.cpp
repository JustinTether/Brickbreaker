#pragma once
#include "BaseObject.h"
#include "engine/guuid.h"

BaseObject::BaseObject() { GUUID = GUUID::GenerateRandomUUID(25); }

void BaseObject::Draw(Engine* Engine) {}

void BaseObject::Update(Engine* Engine, float DeltaTime) {}

void BaseObject::Tick(Engine* Engine, float DeltaTime)
{
  Update(Engine, DeltaTime);
  Draw(Engine);
}
