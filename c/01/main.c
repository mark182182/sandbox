#define _CRTDBG_MAP_ALLOC

// #include "renderer.h"
#include <crtdbg.h>

int main() {
  _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

  // Renderer::render();
  char *leak = malloc(256);

  return 0;
}
