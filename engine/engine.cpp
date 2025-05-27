#include "engine.h"
#include "Clay_Renderer_PGE.h"
#include "GameState.h"
#include "obj/BaseObject.h"
#include <memory>

#define OLC_PGEX_SOUND_H
Engine* Engine::s_instance = nullptr;

Engine::Engine()
{
  sAppName = "BrickBreaker";
  GameState = new GameStateObject();
}

Engine* Engine::Get()
{
  if (s_instance == nullptr)
  {
    s_instance = new Engine();
  }

  return s_instance;
}

void Engine::HandleClayErrors(Clay_ErrorData ErrorData)
{
  std::cout << ErrorData.errorText.chars << "\n";
}

bool Engine::OnUserCreate()
{
  // Persistent menu pointers, these carry over between games/rounds
  GameState = new GameStateObject();
  TileSheet = std::make_unique<olc::Sprite>("assets/sprites/tileset-01.png");

  // Initialize Clay for use
  ClayRenderer = new ClayPGERenderer();
  uint64_t TotalClayMemory = Clay_MinMemorySize();
  Clay_Arena Arena = Clay_CreateArenaWithCapacityAndMemory(
      TotalClayMemory, malloc(TotalClayMemory));
  Clay_Initialize(Arena,
                  (Clay_Dimensions){static_cast<float>(ScreenWidth()),
                                    static_cast<float>(ScreenHeight())},
                  (Clay_ErrorHandler){HandleClayErrors});
  Clay_SetMeasureTextFunction(&ClayPGERenderer::MeasureText, nullptr);

  GameState->InitializeGameState(true);
  return true;
}

bool Engine::OnUserUpdate(float fElapsedTime)
{
  // Clear previous frame
  TimeSinceLastGC += fElapsedTime;
  if (TimeSinceLastGC >= GCInterval)
  {
    GCObjects();
    TimeSinceLastGC = 0;
  }

  Clear(olc::BLACK);

  GameState->Tick(fElapsedTime);

  if (GameState->GetCurrentState() == EGameState::GAME_LOOP)
  {
    for (std::shared_ptr<BaseObject> GameObj : GameObjects)
    {
      if (GameObj && GameObj->bShouldBeGCd)
        continue;

      GameObj->Tick(this, fElapsedTime);
    }
  }

  return true;
}

void Engine::GCObjects()
{
  std::cout << "Initiating GC!" << std::endl;
  int GCCount = 0;
  GameObjects.erase(std::remove_if(GameObjects.begin(), GameObjects.end(),
                                   [&](const std::shared_ptr<BaseObject>& Obj)
                                   {
                                     if (Obj && Obj->bShouldBeGCd)
                                     {
                                       GCCount++;
                                       return true;
                                     }
                                     return false;
                                   }),
                    GameObjects.end());
  std::cout << "GC Complete, num objects GC'd: " << GCCount << std::endl;
}

void Engine::AddNewGameObject(std::shared_ptr<BaseObject> NewObject)
{
  GameObjects.push_back(NewObject);
}

void Engine::RemoveGameObject(std::shared_ptr<BaseObject> ObjectToRemove)
{
  std::string GUUID = ObjectToRemove->GUUID;
  auto it = std::find_if(GameObjects.begin(), GameObjects.end(),
                         [&GUUID](const std::shared_ptr<BaseObject> Obj)
                         { return Obj->GUUID == GUUID; });

  if (it != GameObjects.end())
  {
    auto index = std::distance(GameObjects.begin(), it);

    GameObjects.erase(GameObjects.begin() + index);
  }
}

void Engine::ClearAllGameObjects() { GameObjects.clear(); }
