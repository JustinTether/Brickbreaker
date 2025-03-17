#include "Hud.h"
#include "../engine/engine.h"
#include "../lib/olcPGEX_QuickGUI.h"
#include "MainMenu.h"
#include "engine/GameState.h"
#include "engine/Clay_Renderer_PGE.h"
void Hud::Initialize(Engine* Engine)
{
  bIsInitialized = true; 
}

void Hud::Draw(Engine* Engine)
{
  ClayPGERenderer::UpdateClayState(Engine);
  Clay_BeginLayout();
  // Layout

  CLAY({
    .id = CLAY_ID("HUDContainer"),
    .layout = {.sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0)},
    .padding = CLAY_PADDING_ALL(0),
    .childGap = 3,
    .childAlignment = { .x = CLAY_ALIGN_X_LEFT, .y = CLAY_ALIGN_Y_BOTTOM },
    .layoutDirection = CLAY_TOP_TO_BOTTOM}
  })
  { // HUDContainer
    
    CLAY({
      .id = CLAY_ID("BallsRemainingContainer"),
      .layout = {.sizing = {.width = CLAY_SIZING_FIXED(200), .height = CLAY_SIZING_FIXED(100)},
      .padding = {.left = (uint16_t)Engine->TileSize.x, .bottom = 3},
      .childGap = 3,
      .childAlignment = { .x = CLAY_ALIGN_X_LEFT, .y = CLAY_ALIGN_Y_BOTTOM },
      .layoutDirection = CLAY_LEFT_TO_RIGHT}
    })
    { // BallsRemainingContainer
      CLAY_TEXT(CLAY_STRING("Balls Remaining:"), CLAY_TEXT_CONFIG({.textColor = PixelToClayColor(olc::WHITE), .fontSize = 8}));


      std::string NumBallsRemaining = std::to_string(Engine->GameState->GetNumBallsRemaining());
      
      // This is a bit janky, but CLAY_STRING macro expects a string literal.. Better to just construct the struct ourselves when dealing with dynamic strings
      // All of this is still better than pixel-perfect layouting our UI thank goodness
      Clay_String CString_BallsRemaining = {.length = static_cast<int32_t>(NumBallsRemaining.length()), .chars = NumBallsRemaining.c_str()};
      CLAY_TEXT(
        CString_BallsRemaining,
        CLAY_TEXT_CONFIG({
          .textColor = PixelToClayColor(olc::WHITE), 
          .fontSize = 8
        })
      );

    } // End BallsRemainingContainer
   
  } // End HUDContainer
    
  if(Engine->GetKey(olc::Key::F1).bPressed)
    bDebugClay = !bDebugClay;

  Clay_SetDebugModeEnabled(bDebugClay); 
  Clay_RenderCommandArray RenderCommands = Clay_EndLayout();
  ClayPGERenderer::HandleClayRenderCommands(RenderCommands, Engine);
}
