#include "font.h"
#include <raylib.h>
#include <stdio.h>

void LoadFonts() {

  // FiraCode-Retina.ttf
  Font font =
      LoadFontEx("resources/fonts/firacode/FiraCode-Retina.ttf", 32, 0, 250);

  SetTextureFilter(font.texture, TEXTURE_FILTER_BILINEAR);
  fonts_by_type[FONT_TYPE_FIRA_CODE_RETINA] = font;
}
