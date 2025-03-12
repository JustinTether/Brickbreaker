#include "../lib/olcPixelGameEngine.h"
#include "../lib/olcPGEX_QuickGUI.h"
#include "../lib/clay.h"
#include "stdint.h"
#include "string.h"
#include "stdio.h"
#include "stdlib.h"

#define ClayColorToPixel(Clay_Color) (olc::Pixel) {olc::Pixel(Clay_Color->r, Clay_Color->g, Clay_Color->b)}
#define PixelToClayColor(Pixel) (Clay_Color) {.r = (float)(Pixel.r), .g = (float)(Pixel.g), .b = (float)(Pixel.b), .a = (float)(Pixel.a)}



class ClayPGERenderer
{
public:
  void Clay_PGE_Render(Clay_RenderCommandArray RenderCommands, olc::PixelGameEngine* Engine);
  static inline Clay_Dimensions MeasureText(Clay_StringSlice Text, Clay_TextElementConfig* Config, void* UserData)
  {
    // Clay_TextElementConfig contains members such as fontId, fontSize, letterSpacing etc
    // Note: Clay_String->chars is not guaranteed to be null terminated
    return (Clay_Dimensions) {
            .width = static_cast<float>(Text.length * 8), // <- this will only work for monospace fonts, see the renderers/ directory for more advanced text measurement
            .height = static_cast<float>(8)
    };
  }


};
