#include "Clay_Renderer_PGE.h"
#include "../lib/olcPixelGameEngine.h"

void ClayPGERenderer::Clay_PGE_Render(Clay_RenderCommandArray RenderCommands, olc::PixelGameEngine* Engine)
{
  for (int j = 0; j < RenderCommands.length; j++)
  {
    Clay_RenderCommand* RenderCommand = Clay_RenderCommandArray_Get(&RenderCommands, j);
    Clay_BoundingBox BoundingBox = RenderCommand->boundingBox;

    switch(RenderCommand->commandType)
    {
      case CLAY_RENDER_COMMAND_TYPE_TEXT:
      {
        Clay_TextRenderData* TextData = &RenderCommand->renderData.text;
        Clay_Color* ColorData = &RenderCommand->renderData.text.textColor;

        Engine->DrawString(BoundingBox.x, BoundingBox.y, std::string(TextData->stringContents.chars), olc::Pixel(ColorData->r, ColorData->g, ColorData->b));
        break;
      }

      case CLAY_RENDER_COMMAND_TYPE_RECTANGLE:
      {
        Clay_RectangleRenderData* RectangleRenderData = &RenderCommand->renderData.rectangle;
        Clay_Color* ColorData = &RectangleRenderData->backgroundColor;

        Engine->FillRect(BoundingBox.x, BoundingBox.y, BoundingBox.width, BoundingBox.height, olc::Pixel(ColorData->r, ColorData->g, ColorData->b));
        break;
      }

      case CLAY_RENDER_COMMAND_TYPE_IMAGE:
      {
        Clay_ImageRenderData* ImageRenderData = &RenderCommand->renderData.image;
        olc::Sprite* InSprite = (olc::Sprite*)ImageRenderData->imageData;
        Engine->DrawSprite(BoundingBox.x, BoundingBox.y, InSprite);
      }
      
      default:
      {
        std::cout << "Unhandled Render Command\n";
        break;
      }

    };


  }


};
