#include "Clay_Renderer_PGE.h"
#include <string>

void ClayPGERenderer::HandleClayRenderCommands(
    Clay_RenderCommandArray RenderCommands, olc::PixelGameEngine* Engine)
{
  for (int j = 0; j < RenderCommands.length; j++)
  {
    Clay_RenderCommand* RenderCommand =
        Clay_RenderCommandArray_Get(&RenderCommands, j);
    Clay_BoundingBox BoundingBox = RenderCommand->boundingBox;

    switch (RenderCommand->commandType)
    {
    case CLAY_RENDER_COMMAND_TYPE_TEXT:
    {
      Clay_TextRenderData* TextData = &RenderCommand->renderData.text;
      Clay_Color* ColorData = &RenderCommand->renderData.text.textColor;

      Engine->DrawString(BoundingBox.x, BoundingBox.y,
                         std::string(TextData->stringContents.chars),
                         ClayColorToPixel(ColorData), TextData->fontSize / 8);
      break;
    }

    case CLAY_RENDER_COMMAND_TYPE_RECTANGLE:
    {
      Clay_RectangleRenderData* RectangleRenderData =
          &RenderCommand->renderData.rectangle;
      Clay_Color* ColorData = &RectangleRenderData->backgroundColor;

      Engine->FillRect(BoundingBox.x, BoundingBox.y, BoundingBox.width,
                       BoundingBox.height, ClayColorToPixel(ColorData));
      break;
    }

    case CLAY_RENDER_COMMAND_TYPE_IMAGE:
    {
      Clay_ImageRenderData* ImageRenderData = &RenderCommand->renderData.image;
      olc::Sprite* InSprite = (olc::Sprite*)ImageRenderData->imageData;
      Engine->DrawSprite(BoundingBox.x, BoundingBox.y, InSprite);
      break;
    }

    case CLAY_RENDER_COMMAND_TYPE_BORDER:
    {
      Clay_BorderRenderData* BorderRenderData =
          &RenderCommand->renderData.border;
      Clay_Color* ColorData = &BorderRenderData->color;

      // Left Border
      Engine->FillRect(BoundingBox.x - BorderRenderData->width.left,
                       BoundingBox.y, BorderRenderData->width.left,
                       BoundingBox.height, ClayColorToPixel(ColorData));

      // Top Border
      Engine->FillRect(BoundingBox.x - BorderRenderData->width.left,
                       BoundingBox.y - BorderRenderData->width.top,
                       BoundingBox.width + BorderRenderData->width.left,
                       BorderRenderData->width.top,
                       ClayColorToPixel(ColorData));

      // Right Border
      Engine->FillRect(BoundingBox.x + BoundingBox.width,
                       BoundingBox.y - BorderRenderData->width.top,
                       BorderRenderData->width.right,
                       BoundingBox.height + BorderRenderData->width.top,
                       ClayColorToPixel(ColorData));

      // Bottom Border
      Engine->FillRect(BoundingBox.x - BorderRenderData->width.left,
                       BoundingBox.y + BoundingBox.height,
                       BoundingBox.width + BorderRenderData->width.left +
                           BorderRenderData->width.right,
                       BorderRenderData->width.bottom,
                       ClayColorToPixel(ColorData));
      break;
    }

    case CLAY_RENDER_COMMAND_TYPE_CUSTOM:
    {
      // Your extended struct is passed through
      Clay_CustomRenderData* CustomRenderData =
          &RenderCommand->renderData.custom;
      CustomElementData* CustomElement =
          (CustomElementData*)CustomRenderData->customData;

      if (!CustomElement)
      {
	break;
      }

      switch (CustomElement->type)
      {
      case CUSTOM_ELEMENT_TYPE_SLIDER:
      {
	// Adjust the sliders vPos
	olc::QuickGUI::Slider* SliderObj =
	    std::get<olc::QuickGUI::Slider*>(CustomElement->Obj);

	if (!SliderObj)
	  break;

	// We're a bit limited here, but we'll just blindly center the slider in
	// side of the bounds of the container and rely on the container sizing
	// for positioning
	SliderObj->vPosMin = {BoundingBox.x,
	                      BoundingBox.y + BoundingBox.height / 2};
	SliderObj->vPosMax = {(BoundingBox.x + BoundingBox.width),
	                      (BoundingBox.y + BoundingBox.height / 2)};

	break;
      }
      }
      break;
    }
    default:
    {
      std::cout << "Unhandled Render Command" << "\n";
      break;
    }
    };
  }
};

void ClayPGERenderer::UpdateClayState(olc::PixelGameEngine* Engine)
{
  Clay_SetLayoutDimensions(
      (Clay_Dimensions){static_cast<float>(Engine->ScreenWidth()),
                        static_cast<float>(Engine->ScreenHeight())});
  Clay_SetPointerState((Clay_Vector2){static_cast<float>(Engine->GetMouseX()),
                                      static_cast<float>(Engine->GetMouseY())},
                       Engine->GetMouse(0).bPressed);
  Clay_UpdateScrollContainers(true, Clay_Vector2(0, Engine->GetMouseWheel()),
                              Engine->GetElapsedTime());
}
