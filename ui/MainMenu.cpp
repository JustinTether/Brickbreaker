#include "../lib/olcPGEX_QuickGUI.h"
#include "../lib/olcPGEX_MiniAudio.h"
#include "../engine/Clay_Renderer_PGE.h"
#include "../engine/engine.h"
#include "MainMenu.h"

void MainMenuGUI::Initialize(Engine* EngineInstance)
{
  MainMenuStartButton = new olc::QuickGUI::Button(MainMenuManager,
    "Start",
    { ((float)EngineInstance->ScreenWidth()/2) - MainMenuButtonWidth/2, (float)EngineInstance->ScreenHeight()/2 },
    { MainMenuButtonWidth, MainMenuButtonHeight });

  MainMenuManager.colNormal = olc::BLUE;
  ClickSound = EngineInstance->AudioManager.LoadSound("../assets/sounds/click3.wav");

  //MainMenuText = new olc::QuickGUI::Label(GuiManager, "BrickBreaker", {Engine->ScreenWidth()/2-50, Engine->ScreenHeight()/2-60}, {100.0f, 50.0f}); 

  //MainMenuText->bHasBorder = true;
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
      .childAlignment = {.x = CLAY_ALIGN_X_CENTER, .y = CLAY_ALIGN_Y_CENTER},
      .layoutDirection = CLAY_TOP_TO_BOTTOM},
      .backgroundColor = {(float)olc::BLUE.r, (float)olc::BLUE.g, (float)olc::BLUE.b, (float)olc::BLUE.a}
    })
    {
      CLAY_TEXT(CLAY_STRING("BrickBreaker"), CLAY_TEXT_CONFIG({.textColor = {(float)olc::WHITE.r, (float)olc::WHITE.g, (float)olc::WHITE.b, (float)olc::WHITE.a}, .fontSize = 32}));
    }
  };

  if(Engine->GetKey(olc::Key::D).bPressed)
    bDebugClay = !bDebugClay;

  Clay_SetDebugModeEnabled(bDebugClay);
  Clay_RenderCommandArray RenderCommands = Clay_EndLayout();
  ClayRenderer->Clay_PGE_Render(RenderCommands, Engine);
}
