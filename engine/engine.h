#ifndef ENGINE_H
#define ENGINE_H
#pragma once
#include "../lib/clay.h"
#include "../lib/olcPGEX_MiniAudio.h"
#include "../lib/olcPGEX_QuickGUI.h"
#include "../lib/olcPixelGameEngine.h"
#include "obj/BaseObject.h"
class Bat;
class Ball;
class MainMenuGUI;
class GameOverGUI;
class PauseMenu;
class BaseBrick;
class Hud;
class GameStateObject;
class ClayPGERenderer;
class IncreaseBatWidthUpgrade;
class BaseObject;

class Engine : public olc::PixelGameEngine
{

private:
  Engine();
  Engine(const Engine&) = delete;
  Engine& operator=(const Engine&) = delete;

  // singleton of our Engine class
  static Engine* s_instance;

public:
  static Engine* Get();
  // CLAY Renderer
  ClayPGERenderer* ClayRenderer;

  olc::QuickGUI::Manager GuiManager;
  olc::vi2d TileSize = {16, 16};

  std::unique_ptr<olc::Sprite> TileSheet;

  // Audio Manager through MiniAudio
  olc::MiniAudio AudioManager;

  GameStateObject* GameState;

  virtual bool OnUserCreate() override;
  virtual bool OnUserUpdate(float fElapsedTime) override;
  static void HandleClayErrors(Clay_ErrorData ErrorData);

  template <class T>
  std::vector<std::shared_ptr<BaseObject>> GetGameObjectOfType()
  {
    std::vector<std::shared_ptr<BaseObject>> FoundObjects;
    for (std::shared_ptr<BaseObject> Obj : GameObjects)
    {
      if (std::shared_ptr CastedObject = std::static_pointer_cast<T>(Obj))
      {
        FoundObjects.push_back(Obj);
      }
    }

    return FoundObjects;
  }

  int main();
  void AddNewGameObject(std::shared_ptr<BaseObject> NewObject);
  void RemoveGameObject(std::shared_ptr<BaseObject> ObjectToRemove);
  void ClearAllGameObjects();

private:
  std::vector<std::shared_ptr<BaseObject>> GameObjects;
  void GCObjects();
};
#endif
