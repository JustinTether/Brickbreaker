#include "OptionsMenu.h"
#include "engine/AudioManager.h"
#include "engine/engine.h"

OptionsMenu::OptionsMenu() {}

void OptionsMenu::Draw()
{
  // Reset the frame arena offset for the memory storage being used here
  FrameArena.offset = 0;

  // Initializing Clay state
  ClayPGERenderer::UpdateClayState(Engine::Get());
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

    CLAY_TEXT(CLAY_STRING("Options"),
              CLAY_TEXT_CONFIG(
                  {.textColor = PixelToClayColor(olc::WHITE), .fontSize = 24}));
    CLAY(
        {.id = CLAY_ID("Inner Container"),
         .layout = {.sizing = {.width = CLAY_SIZING_FIT(0),
                               .height = CLAY_SIZING_FIT(0)},
                    .padding = {.left = 5, .right = 5, .top = 10, .bottom = 10},
                    .childGap = 5,
                    .childAlignment = {.x = CLAY_ALIGN_X_CENTER,
                                       .y = CLAY_ALIGN_Y_CENTER},
                    .layoutDirection = CLAY_TOP_TO_BOTTOM},
         .backgroundColor = PixelToClayColor(olc::DARK_BLUE),
         .border = {.color = PixelToClayColor(olc::WHITE),
                    .width = {.left = 1, .right = 1, .top = 1, .bottom = 1}}})
    {

      CLAY_TEXT(CLAY_STRING("Music Volume"),
                CLAY_TEXT_CONFIG({.textColor = PixelToClayColor(olc::WHITE),
                                  .fontSize = 8}));
      CLAY(
          {.id = CLAY_ID("MusicVolumeSliderContainer"),
           .layout = {.sizing = {.width = CLAY_SIZING_FIT(0),
                                 .height = CLAY_SIZING_FIT(0)},
                      .padding = {.left = 5, .right = 5, .top = 0, .bottom = 5},
                      .childGap = 0,
                      .childAlignment = {.x = CLAY_ALIGN_X_CENTER,
                                         .y = CLAY_ALIGN_Y_CENTER},
                      .layoutDirection = CLAY_TOP_TO_BOTTOM}})
      {
	CustomElementData* MusicSliderData =
	    (CustomElementData*)((char*)FrameArena.memory + FrameArena.offset);
	*MusicSliderData = (CustomElementData){
	    .type = CUSTOM_ELEMENT_TYPE_SLIDER, .Obj = MusicVolumeSlider};

	CLAY({.id = CLAY_ID("MusicVolumeSlider"),
	      .layout = {.sizing = {.width = CLAY_SIZING_FIXED(100),
	                            .height = CLAY_SIZING_FIXED(25)}},
	      .custom = MusicSliderData}){};
	FrameArena.offset += sizeof(CustomElementData);

      } // END MUSICVOLUMESLIDERCONTAINER

      CLAY_TEXT(CLAY_STRING("Effects Volume"),
                CLAY_TEXT_CONFIG({.textColor = PixelToClayColor(olc::WHITE),
                                  .fontSize = 8}));

      CLAY(
          {.id = CLAY_ID("EffectsVolumeSliderContainer"),
           .layout = {.sizing = {.width = CLAY_SIZING_FIT(0),
                                 .height = CLAY_SIZING_FIT(0)},
                      .padding = {.left = 5, .right = 5, .top = 0, .bottom = 5},
                      .childGap = 0,
                      .childAlignment = {.x = CLAY_ALIGN_X_CENTER,
                                         .y = CLAY_ALIGN_Y_CENTER},
                      .layoutDirection = CLAY_TOP_TO_BOTTOM}})
      {
	CustomElementData* EffectsSliderData =
	    (CustomElementData*)((char*)FrameArena.memory + FrameArena.offset);
	*EffectsSliderData = (CustomElementData){
	    .type = CUSTOM_ELEMENT_TYPE_SLIDER, .Obj = EffectsVolumeSlider};

	CLAY({.id = CLAY_ID("EffectVolumeSlider"),
	      .layout = {.sizing = {.width = CLAY_SIZING_FIXED(100),
	                            .height = CLAY_SIZING_FIXED(25)}},
	      .custom = EffectsSliderData}){};
	FrameArena.offset += sizeof(CustomElementData);

      } // END EFFECTSVOLUMESLIDERCONTAINER

      CLAY({.id = CLAY_ID("BackButton"),
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
	CLAY_TEXT(CLAY_STRING("Back"),
	          CLAY_TEXT_CONFIG({.textColor = PixelToClayColor(olc::WHITE),
	                            .fontSize = 8}));

	if (Engine::Get()->GetMouse(0).bPressed &&
	    Clay_PointerOver(CLAY_ID("BackButton")))
	{
	  bIsBackButtonPressed = true;
	}
	else
	  bIsBackButtonPressed = false;
      };

    } // END INNER CONTANER
  };

  Clay_RenderCommandArray RenderCommands = Clay_EndLayout();
  ClayPGERenderer::HandleClayRenderCommands(RenderCommands, Engine::Get());
  GUIManager.Update(Engine::Get());
  GUIManager.Draw(Engine::Get());

  if (PreviousMusicVolume != MusicVolumeSlider->fValue)
  {
    MusicVolume = MusicVolumeSlider->fValue;
    PreviousMusicVolume = MusicVolume;
    std::cout << "Music Volume updated: " << MusicVolume << std::endl;
    AudioManager::Get()->SetMusicVolume(MusicVolume);
  }

  if (PreviousEffectsVolume != EffectsVolumeSlider->fValue)
  {
    EffectsVolume = EffectsVolumeSlider->fValue;
    PreviousEffectsVolume = EffectsVolume;
    std::cout << "Effects Volume updated: " << EffectsVolume << std::endl;
    AudioManager::Get()->SetEffectsVolume(EffectsVolume);
  }
}

void OptionsMenu::Initialize()
{
  MusicVolumeSlider =
      new olc::QuickGUI::Slider(GUIManager, olc::vf2d(0, 0), olc::vf2d(0, 0), 0,
                                1.0f, AudioManager::Get()->GetMusicVolume());

  EffectsVolumeSlider =
      new olc::QuickGUI::Slider(GUIManager, olc::vf2d(0, 0), olc::vf2d(0, 0), 0,
                                1.0f, AudioManager::Get()->GetEffectsVolume());

  FrameArena = (Arena){.memory = malloc(1024)};
  MusicVolume = 1.0f;
  bIsInitialized = true;
}
