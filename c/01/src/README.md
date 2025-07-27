# CA Renderer

This project is a thesis work for rendering 2D/3D cellular automata in C.

# Notes on the implementation

- All structs are in Pascal Case, e.g. `Renderer`, `Menu`, `Cells2D`
- All functions are in Pascal Case, e.g. `LoadFonts` or Pascal Snake Case, e.g. `Render_Window`, `Menu_Init`, `Generator_NextGeneration`, when they belong to a given struct. Except those that are only used internally in each module, which are prefixed with `__`, e.g. `__CheckNeighbours`.
- Instead of using namespaces like in C++, or creating a struct and storing function pointers in it, it's advised to just use a prefix before the name of the function. Instead of `arenaAllocator.init()` we would have `Arena_Init()` (Pascal Snake Case), which is much less code and easier.
- Enums are prefixed with the module name, e.g. `RenderMode`, `FontType`, and use full upper snake case for the enum values, e.g. `RENDER_MODE_2D`, `FONT_TYPE_FIRA_CODE_RETINA`.

# Testing

- The following folder structure is used for testing in the `tests/` directory:
  - `unit` - contains the unit test files that run the functions in isolation
  - `integration/` - contains integration tests that run the internal parts of the renderer, such as the menu, and asserts that they work correctly in conjunction with the renderer
  - `e2e/` - few end-to-end tests that run the renderer with preconfigured settings and asserts via screenshot comparison
  - `scratch/` - a place for experiments and temporary tests that don't fit into the other categories; example: `ray.c` for testing different raylib related features
