#ifndef FONT_H
#define FONT_H

#include <stdio.h>
#include <raylib.h>

// using FontType as the name would clash with raylib
typedef enum RenderFontType {
  FONT_TYPE_FIRA_CODE_RETINA,
  MAX_FONT_TYPE
} RenderFontType;

static Font fonts_by_type[MAX_FONT_TYPE];

#endif
