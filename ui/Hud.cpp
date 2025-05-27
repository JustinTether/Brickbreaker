#include "Hud.h"
#include "../engine/engine.h"
#include "MainMenu.h"
#include "engine/Clay_Renderer_PGE.h"
#include "engine/GameState.h"
#include "obj/BaseObject.h"
#include "obj/upgrades/BaseUpgrade.h"
void Hud::Initialize(Engine* Engine) { bIsInitialized = true; }

void Hud::Draw(Engine* Engine)
{
  ClayPGERenderer::UpdateClayState(Engine);
  Clay_BeginLayout();
  UIStrings.clear();
  // Layout

  CLAY({.id = CLAY_ID("HUDContainer"),
        .layout = {.sizing = {.width = CLAY_SIZING_GROW(0),
                              .height = CLAY_SIZING_GROW(0)},
                   .padding = CLAY_PADDING_ALL(0),
                   .childGap = 3,
                   .childAlignment = {.x = CLAY_ALIGN_X_LEFT,
                                      .y = CLAY_ALIGN_Y_BOTTOM},
                   .layoutDirection = CLAY_TOP_TO_BOTTOM}})
  { // HUDContainer
    CLAY({.id = CLAY_ID("TextContainer"),
          .layout = {
              .sizing = {.width = CLAY_SIZING_GROW(0),
                         .height = CLAY_SIZING_GROW(0)},
              .padding = {.left = (uint16_t)Engine->TileSize.x, .bottom = 3},
              .childGap = 3,
              .childAlignment = {.x = CLAY_ALIGN_X_LEFT,
                                 .y = CLAY_ALIGN_Y_BOTTOM},
              .layoutDirection = CLAY_TOP_TO_BOTTOM}})
    {
      CLAY({.id = CLAY_ID("BallsRemainingContainer"),
            .layout = {
                .sizing = {.width = CLAY_SIZING_FIXED(200),
                           .height = CLAY_SIZING_FIXED(100)},
                .padding = {.left = (uint16_t)Engine->TileSize.x, .bottom = 3},
                .childGap = 3,
                .childAlignment = {.x = CLAY_ALIGN_X_LEFT,
                                   .y = CLAY_ALIGN_Y_BOTTOM},
                .layoutDirection = CLAY_LEFT_TO_RIGHT}})
      { // BallsRemainingContainer
        CLAY_TEXT(CLAY_STRING("Balls Remaining:"),
                  CLAY_TEXT_CONFIG({.textColor = PixelToClayColor(olc::WHITE),
                                    .fontSize = 8}));

        UIStrings.push_back(
            std::to_string(Engine->GameState->GetNumBallsRemaining()));

        const std::string& NumBallsRemaining = UIStrings.back();

        // This is a bit hanky, but CLAY_STRING macro expects a string literal..
        // Better to just construct the struct ourselves when dealing with
        // dynamic strings
        Clay_String CString_BallsRemaining = {
            .length = static_cast<int32_t>(NumBallsRemaining.length()),
            .chars = NumBallsRemaining.c_str()};
        CLAY_TEXT(CString_BallsRemaining,
                  CLAY_TEXT_CONFIG({.textColor = PixelToClayColor(olc::WHITE),
                                    .fontSize = 8}));

      } // End BallsRemainingContainer

      std::vector<std::shared_ptr<BaseObject>> CurrentUpgrades =
          Engine::Get()->GetGameObjectOfType<BaseUpgrade>();

      for (std::shared_ptr<BaseObject> Obj : CurrentUpgrades)
      {
        if (!Obj)
          continue;

        if (Obj->bShouldBeGCd)
          continue;

        std::shared_ptr<BaseUpgrade> Upgrade =
            std::static_pointer_cast<BaseUpgrade>(Obj);

        CLAY({.layout = {.sizing = {.width = CLAY_SIZING_FIT(0),
                                    .height = CLAY_SIZING_FIT(0)},
                         .padding = {.left = (uint16_t)Engine->TileSize.x,
                                     .bottom = 3},
                         .childGap = 3,
                         .childAlignment = {.x = CLAY_ALIGN_X_LEFT,
                                            .y = CLAY_ALIGN_Y_BOTTOM},
                         .layoutDirection = CLAY_LEFT_TO_RIGHT}})
        { // UpgradeContainer

          // Create a new Text object for each upgrade with the current duration
          UIStrings.push_back(Upgrade->Name);
          const std::string& UpgradeName = UIStrings.back();

          Clay_String CString_UpgradeName = {
              .length = static_cast<int32_t>(UpgradeName.length()),
              .chars = UpgradeName.c_str()};

          CLAY_TEXT(CString_UpgradeName,
                    CLAY_TEXT_CONFIG({.textColor = PixelToClayColor(olc::WHITE),
                                      .fontSize = 8}));

          UIStrings.push_back(std::to_string(Upgrade->UpgradeLifespan));
          const std::string& UpgradeLifespan = UIStrings.back();

          Clay_String CString_TimeRemaining = {
              .length = static_cast<int32_t>(UpgradeLifespan.length()),
              .chars = UpgradeLifespan.c_str()};
          CLAY_TEXT(CString_TimeRemaining,
                    CLAY_TEXT_CONFIG({.textColor = PixelToClayColor(olc::WHITE),
                                      .fontSize = 8}));
        }
      }

    } // END TEXT CONTAINER

  } // End HUDContainer

  if (Engine->GetKey(olc::Key::F1).bPressed)
    bDebugClay = !bDebugClay;

  Clay_SetDebugModeEnabled(bDebugClay);
  Clay_RenderCommandArray RenderCommands = Clay_EndLayout();
  ClayPGERenderer::HandleClayRenderCommands(RenderCommands, Engine);
}
