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
  Clay_UpdateScrollContainers(true, (Clay_Vector2)Engine->GetMouseWheel(), Engine->GetElapsedTime());

  Clay_BeginLayout();

  CLAY({
    .id = CLAY_ID("OuterContainer"),
    .layout = {.sizing = {.width = CLAY_SIZING_GROW(0), .height = CLAY_SIZING_GROW(0)},
    .padding = CLAY_PADDING_ALL(16),
    .childGap = 16,
    .childAlignment = {.x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER},
    .layoutDirection = CLAY_TOP_TO_BOTTOM},
    .backgroundColor = {(float)olc::BLACK.r, (float)olc::BLACK.g, (float)olc::BLACK.b, (float)olc::BLACK.a}

  }) {

    CLAY({
      .id = CLAY_ID("Inner Container"),
      .layout = {.sizing = {.width = CLAY_SIZING_FIXED(150), .height = CLAY_SIZING_FIXED(150)},
      .padding = CLAY_PADDING_ALL(5),
      .childGap = 10,
      .childAlignment = {.x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER},
      .layoutDirection = CLAY_TOP_TO_BOTTOM},
      .backgroundColor = {(float)olc::BLUE.r, (float)olc::BLUE.g, (float)olc::BLUE.b, (float)olc::BLUE.a},
      .border = {.color = {(float)olc::WHITE.r, (float)olc::WHITE.g, (float)olc::WHITE.b}, .width = {.left = 2, .right = 2, .top = 2, .bottom = 2}}
    })
    {
      CLAY_TEXT(CLAY_STRING("BrickBreaker"), CLAY_TEXT_CONFIG({.textColor = {(float)olc::WHITE.r, (float)olc::WHITE.g, (float)olc::WHITE.b, (float)olc::WHITE.a}, .fontSize = 32}));
      CLAY({
        .id = CLAY_ID("StartButton"),
        .layout = {.sizing = {.width = CLAY_SIZING_FIXED(50), .height = CLAY_SIZING_FIXED(25)},
        .childAlignment = {.x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER},
        .layoutDirection = CLAY_TOP_TO_BOTTOM},
        .backgroundColor = {(float)olc::GREY.r, (float)olc::GREY.g, (float)olc::GREY.b, (float)olc::GREY.a},
        .border = {.color = {(float)olc::WHITE.r, (float)olc::WHITE.g, (float)olc::WHITE.b}, .width = {.left = 2, .right = 2, .top = 2, .bottom = 2}}

      })
      {
        CLAY_TEXT(CLAY_STRING("Start"), CLAY_TEXT_CONFIG({.textColor = {(float)olc::WHITE.r, (float)olc::WHITE.g, (float)olc::WHITE.b, (float)olc::WHITE.a}, .fontSize = 32}));

        // Handle Mouse clicking the Resume button
        if(Engine->GetMouse(0).bPressed && Clay_PointerOver(CLAY_ID("StartButton")))
        {
          bIsStartButtonPressed = true;
        }
        else
          bIsStartButtonPressed = false;

      };
    }
  };

  if(Engine->GetKey(olc::Key::D).bPressed)
    bDebugClay = !bDebugClay;

  Clay_SetDebugModeEnabled(bDebugClay);
  Clay_RenderCommandArray RenderCommands = Clay_EndLayout();
  ClayRenderer->Clay_PGE_Render(RenderCommands, Engine);
}
