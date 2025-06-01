#include "../engine/Clay_Renderer_PGE.h"
#include "../engine/engine.h"
#include "PauseMenu.h"
#include "engine/AudioManager.h"
#include "olcPGEX_QuickGUI.h"

void PauseMenu::Initialize(Engine* Engine)
{
  bIsInitialized = true;
  ClickSound =
      AudioManager::Get()->RegisterNewSound("assets/sounds/click3.wav");
}

void PauseMenu::Draw(Engine* Engine)
{
  // Initializing Clay state
  ClayPGERenderer::UpdateClayState(Engine);

  Clay_BeginLayout();

  CLAY({.id = CLAY_ID("OuterContainer"),
        .layout = {.sizing = {.width = CLAY_SIZING_GROW(0),
                              .height = CLAY_SIZING_GROW(0)},
                   .padding = CLAY_PADDING_ALL(16),
                   .childGap = 16,
                   .childAlignment = {.x = CLAY_ALIGN_X_CENTER,
                                      .y = CLAY_ALIGN_Y_CENTER},
                   .layoutDirection = CLAY_TOP_TO_BOTTOM},
        .backgroundColor = PixelToClayColor(olc::BLACK)

  })
  {

    CLAY_TEXT(CLAY_STRING("Paused"),
              CLAY_TEXT_CONFIG(
                  {.textColor = PixelToClayColor(olc::WHITE), .fontSize = 24}));
    CLAY(
        {.id = CLAY_ID("Inner Container"),
         .layout = {.sizing = {.width = CLAY_SIZING_FIT(0),
                               .height = CLAY_SIZING_FIT(0)},
                    .padding = {.left = 5, .right = 5, .top = 10, .bottom = 10},
                    .childGap = 10,
                    .childAlignment = {.x = CLAY_ALIGN_X_CENTER,
                                       .y = CLAY_ALIGN_Y_CENTER},
                    .layoutDirection = CLAY_TOP_TO_BOTTOM},
         .backgroundColor = PixelToClayColor(olc::DARK_BLUE),
         .border = {.color = PixelToClayColor(olc::WHITE),
                    .width = {.left = 1, .right = 1, .top = 1, .bottom = 1}}})
    {
      CLAY({.id = CLAY_ID("ResumeButton"),
            .layout = {.sizing = {.width = CLAY_SIZING_FIT(0),
                                  .height = CLAY_SIZING_FIT(0)},
                       .padding = {8, 8, 15, 15},
                       .childAlignment = {.x = CLAY_ALIGN_X_CENTER,
                                          .y = CLAY_ALIGN_Y_CENTER},
                       .layoutDirection = CLAY_TOP_TO_BOTTOM},
            .backgroundColor = Clay_Hovered()
                                   ? PixelToClayColor(olc::GREY)
                                   : PixelToClayColor(olc::DARK_GREY),
            .border = {.color = PixelToClayColor(olc::WHITE),
                       .width = {.left = 1, .right = 1, .top = 1, .bottom = 1}}

      })
      {
	CLAY_TEXT(CLAY_STRING("Resume"),
	          CLAY_TEXT_CONFIG({.textColor = PixelToClayColor(olc::WHITE),
	                            .fontSize = 8}));

	// Handle Mouse clicking the Start button
	if (Engine->GetMouse(0).bPressed &&
	    Clay_PointerOver(CLAY_ID("ResumeButton")))
	{
	  bIsResumeButtonClicked = true;
	}
	else
	  bIsResumeButtonClicked = false;
      }

      CLAY({.id = CLAY_ID("OptionsButton"),
            .layout = {.sizing = {.width = CLAY_SIZING_FIT(0),
                                  .height = CLAY_SIZING_FIT(0)},
                       .padding = {8, 8, 15, 15},
                       .childAlignment = {.x = CLAY_ALIGN_X_CENTER,
                                          .y = CLAY_ALIGN_Y_CENTER},
                       .layoutDirection = CLAY_TOP_TO_BOTTOM},
            .backgroundColor = Clay_Hovered()
                                   ? PixelToClayColor(olc::GREY)
                                   : PixelToClayColor(olc::DARK_GREY),
            .border = {.color = PixelToClayColor(olc::WHITE),
                       .width = {.left = 1, .right = 1, .top = 1, .bottom = 1}}

      })
      {
	CLAY_TEXT(CLAY_STRING("Options"),
	          CLAY_TEXT_CONFIG({.textColor = PixelToClayColor(olc::WHITE),
	                            .fontSize = 8}));

	// Handle Mouse clicking the Start button
	if (Engine->GetMouse(0).bPressed &&
	    Clay_PointerOver(CLAY_ID("OptionsButton")))
	{
	  bIsOptionsButtonclicked = true;
	}
	else
	  bIsOptionsButtonclicked = false;
      }
    }
  }

  // Clay_SetDebugModeEnabled(bDebugClay);
  Clay_RenderCommandArray RenderCommands = Clay_EndLayout();
  ClayPGERenderer::HandleClayRenderCommands(RenderCommands, Engine);
}
