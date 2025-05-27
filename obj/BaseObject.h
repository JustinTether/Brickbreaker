//
// Created by justin on 2/11/25.
//
#pragma once
#ifndef BASEOBJECT_H
#define BASEOBJECT_H
#include "../lib/olcPixelGameEngine.h"

class Engine;

class BaseObject
{

protected:
public:
  BaseObject();
  virtual void Draw(Engine* Engine);
  virtual void Update(Engine* Engine, float DeltaTime);

  bool bShouldBeGCd = false;
  virtual void Tick(Engine* Engine, float DeltaTime);

  std::string GUUID;
  std::string Name;
};

#endif // BASEOBJECT_H
