#include "../lib/olcPGEX_QuickGUI.h"
#include "../lib/olcPGEX_MiniAudio.h"
#include "../engine/Clay_Renderer_PGE.h"
#include "../engine/engine.h"
#include "MainMenu.h"

void MainMenuGUI::Initialize(Engine* EngineInstance)
{

  ClickSound = EngineInstance->AudioManager.LoadSound("../assets/sounds/click3.wav");
  ClayRenderer = new ClayPGERenderer();
  bIsInitialized = true;
}

void MainMenuGUI::Draw(Engine* Engine)
{
  // Initializing Clay state
  Clay_SetLayoutDimensions((Clay_Dimensions){static_cast<float>(Engine->ScreenWidth()), static_cast<float>(Engine->ScreenHeight())});
  Clay_SetPointerState((Clay_Vector2){static_cast<float>(Engine->GetMouseX()), static_cast<float>(Engine->GetMouseY())}, Engine->GetMouse(0).bPressed);
  Clay_UpdateScrollContainers(true, Clay_Vector2(0, Engine->GetMouseWheel()), Engine->GetElapsedTime());

  Clay_BeginLayout();

  CLAY({
    .id = CLAY_ID("OuterContainer"),
    .layout = {.sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0)},
    .padding = CLAY_PADDING_ALL(16),
    .childGap = 16,
    .childAlignment = {.x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER},
    .layoutDirection = CLAY_TOP_TO_BOTTOM},
    .backgroundColor = PixelToClayColor(olc::BLACK) 

  }) {

    CLAY_TEXT(CLAY_STRING("BrickBreaker"), CLAY_TEXT_CONFIG({.textColor = PixelToClayColor(olc::WHITE), .fontSize = 32}));
    
    CLAY({
      .id = CLAY_ID("Inner Container"),
      .layout = {.sizing = {.width = CLAY_SIZING_FIT(0), .height = CLAY_SIZING_FIT(0)},
      .padding = {.left = 5, .right = 5, .top = 10, .bottom = 10},
      .childGap = 10,
      .childAlignment = {.x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER},
      .layoutDirection = CLAY_TOP_TO_BOTTOM},
      .backgroundColor = PixelToClayColor(olc::BLUE),
      .border = {.color = PixelToClayColor(olc::WHITE), .width = {.left = 1, .right = 1, .top = 1, .bottom = 1}}
    })
    {
      CLAY({
        .id = CLAY_ID("StartButton"),
        .layout = {.sizing = {.width = CLAY_SIZING_FIXED(50), .height = CLAY_SIZING_FIXED(25)},
        .childAlignment = {.x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER},
        .layoutDirection = CLAY_TOP_TO_BOTTOM},
        .backgroundColor = Clay_Hovered() ? PixelToClayColor(olc::GREY) : PixelToClayColor(olc::DARK_GREY),
        .border = {.color = PixelToClayColor(olc::WHITE), .width = {.left = 1, .right = 1, .top = 1, .bottom = 1}}

      })
      {
        CLAY_TEXT(CLAY_STRING("Start"), CLAY_TEXT_CONFIG({.textColor = PixelToClayColor(olc::WHITE), .fontSize = 32}));

        // Handle Mouse clicking the Start button
        if(Engine->GetMouse(0).bPressed && Clay_PointerOver(CLAY_ID("StartButton")))
        {
          bIsStartButtonPressed = true;
        }
        else
          bIsStartButtonPressed = false;

      }
      CLAY({
        .id = CLAY_ID("QuitButton"),
        .layout = {.sizing = {.width = CLAY_SIZING_FIXED(50), .height = CLAY_SIZING_FIXED(25)},
        .childAlignment = {.x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER},
        .layoutDirection = CLAY_TOP_TO_BOTTOM},
        .backgroundColor = Clay_Hovered() ? PixelToClayColor(olc::GREY) : PixelToClayColor(olc::DARK_GREY),
        .border = {.color = PixelToClayColor(olc::WHITE), .width = {.left = 1, .right = 1, .top = 1, .bottom = 1}}

      })
      {
        CLAY_TEXT(CLAY_STRING("Quit"), CLAY_TEXT_CONFIG({.textColor = PixelToClayColor(olc::WHITE), .fontSize = 32}));

      };
    }
  };

  if(Engine->GetKey(olc::Key::D).bPressed)
    bDebugClay = !bDebugClay;

  Clay_SetDebugModeEnabled(bDebugClay);
  Clay_RenderCommandArray RenderCommands = Clay_EndLayout();
  ClayRenderer->Clay_PGE_Render(RenderCommands, Engine);
}
