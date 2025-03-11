#include "Hud.h"
#include "../engine/engine.h"
#include "../lib/olcPGEX_QuickGUI.h"
#include "engine/GameState.h"
void Hud::Initialize(Engine* Engine)
{
  BallsRemainingLabel = new olc::QuickGUI::Label(HudManager, "Balls Remaining: ", {60, static_cast<float>(Engine->ScreenHeight()-20)}, {20, 20});
  BallsRemainingNumber = new olc::QuickGUI::Label(HudManager, std::to_string(Engine->GameState->GetNumBallsRemaining()), {BallsRemainingLabel->vPos.x + BallsRemainingLabel->vPos.x, static_cast<float>(Engine->ScreenHeight()-20)}, {20, 20});

  bIsInitialized = true; 
}
