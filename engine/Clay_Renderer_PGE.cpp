#include "Clay_Renderer_PGE.h"
#include "../lib/olcPixelGameEngine.h"

Clay_Color COLOR_GREY = {(float)olc::GREY.r, (float)olc::GREY.g, (float)olc::GREY.b, (float)olc::GREY.a};
Clay_Color COLOR_DARKGREY = {(float)olc::DARK_GREY.r, (float)olc::DARK_GREY.g, (float)olc::DARK_GREY.b, (float)olc::DARK_GREY.a};
Clay_Color COLOR_WHITE = {(float)olc::WHITE.r, (float)olc::WHITE.g, (float)olc::WHITE.b, (float)olc::WHITE.a};

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

        Engine->DrawString(BoundingBox.x, BoundingBox.y, std::string(TextData->stringContents.chars), ClayColorToPixel(ColorData));
        break;
      }

      case CLAY_RENDER_COMMAND_TYPE_RECTANGLE:
      {
        Clay_RectangleRenderData* RectangleRenderData = &RenderCommand->renderData.rectangle;
        Clay_Color* ColorData = &RectangleRenderData->backgroundColor;

        Engine->FillRect(BoundingBox.x, BoundingBox.y, BoundingBox.width, BoundingBox.height, ClayColorToPixel(ColorData));
        break;
      }

      case CLAY_RENDER_COMMAND_TYPE_IMAGE:
      {
        Clay_ImageRenderData* ImageRenderData = &RenderCommand->renderData.image;
        olc::Sprite* InSprite = (olc::Sprite*)ImageRenderData->imageData;
        Engine->DrawSprite(BoundingBox.x, BoundingBox.y, InSprite);
      }

      case CLAY_RENDER_COMMAND_TYPE_BORDER:
      {
        Clay_BorderRenderData* BorderRenderData = &RenderCommand->renderData.border;
        Clay_Color* ColorData = &BorderRenderData->color;
        
        // Left Border
        Engine->FillRect(BoundingBox.x - BorderRenderData->width.left,
                         BoundingBox.y, 
                         BorderRenderData->width.left, 
                         BoundingBox.height, 
                         ClayColorToPixel(ColorData));

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
                         BoundingBox.width + BorderRenderData->width.left + BorderRenderData->width.right, 
                         BorderRenderData->width.bottom, 
                         ClayColorToPixel(ColorData));
      }
      default:
      {
        std::cout << "Unhandled Render Command\n";
        break;
      }

    };


  }


};
