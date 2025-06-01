#include "../lib/clay.h"
#include "../lib/olcPixelGameEngine.h"
#include "lib/olcPGEX_QuickGUI.h"
#include "stdint.h"
#include "stdlib.h"
#include <variant>

#define ClayColorToPixel(Clay_Color)                                           \
  (olc::Pixel) { olc::Pixel(Clay_Color->r, Clay_Color->g, Clay_Color->b) }
#define PixelToClayColor(Pixel)                                                \
  (Clay_Color)                                                                 \
  {                                                                            \
    .r = (float)(Pixel.r), .g = (float)(Pixel.g), .b = (float)(Pixel.b),       \
    .a = (float)(Pixel.a)                                                      \
  }

enum CustomElementType
{
  CUSTOM_ELEMENT_TYPE_SLIDER,
};

struct CustomElementData
{
  CustomElementType type;
  std::variant<olc::QuickGUI::Slider*> Obj;
};

struct Arena
{
  void* memory;
  uintptr_t offset;
};

class ClayPGERenderer
{
public:
  static void HandleClayRenderCommands(Clay_RenderCommandArray RenderCommands,
                                       olc::PixelGameEngine* Engine);
  static void UpdateClayState(olc::PixelGameEngine* Engine);
  static inline Clay_Dimensions MeasureText(Clay_StringSlice Text,
                                            Clay_TextElementConfig* Config,
                                            void* UserData)
  {
    // Clay_TextElementConfig contains members such as fontId, fontSize,
    // letterSpacing etc Note: Clay_String->chars is not guaranteed to be null
    // terminated

    return (Clay_Dimensions){
        // PixelGameEngine default font is monospace and each character is 8px
        // PixelGameEngine::DrawString has an optional integer scaling
        // parameter, so a '2' will result in 16px wide characters
        // This means we only need to divide the desired fontSize by the default
        // character width to get an integer scaling value, and the correct
        // character width
        .width = static_cast<float>(
            (Text.length * 8) *
            (Config->fontSize /
             (float)8)), // <- this will only work for monospace fonts, see the
                         // renderers/ directory for more advanced text
                         // measurement
        .height = static_cast<float>(8) * (Config->fontSize / (float)8)};
  }
};
