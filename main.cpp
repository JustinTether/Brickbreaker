#include "main.h"
#include "engine/GameState.h"
int main()
{
  Engine* demo = Engine::Get();
  if (demo->Construct(demo->GameState->MapWidth * demo->TileSize.x,
                      demo->GameState->MapHeight * demo->TileSize.y, 2, 2))
    demo->Start();
  return 0;
}
