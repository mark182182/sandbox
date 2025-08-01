# The rest of the project has been moved to https://github.com/mark182182/ca-thesis

# CA Renderer

This project is part of a thesis work for rendering 2D/3D cellular automata in C.

# Notes on AI usage

- Code generation for C code has been disabled in the `.vscode/settings.json` file, search for `Disable GitHub Copilot for C files` string.
- Ideation and brainstorming for the project structure and functionality were assisted by AI.

# Notes on the implementation

- All structs are in Pascal Case, e.g. `Renderer`, `Menu`, `Cells2D`
- All functions are in Pascal Case, e.g. `LoadFonts` or Pascal Snake Case, e.g. `Render_Window`, `Menu_Init`, `Generator_NextGeneration`, when they belong to a given struct. Except those that are only used internally in each module, which are prefixed with `__`, e.g. `__CheckNeighbours`.
- Instead of using namespaces like in C++, or creating a struct and storing function pointers in it, it's advised to just use a prefix before the name of the function. Instead of `arenaAllocator.init()` we would have `Arena_Init()` (Pascal Snake Case), which is much less code and easier.
- Enums are prefixed with the module name, e.g. `RenderMode`, `FontType`, and use full upper snake case for the enum values, e.g. `RENDER_MODE_2D`, `FONT_TYPE_FIRA_CODE_RETINA`.
- Enums are used when multiple values need to be represented, such as render modes or font types. They are defined in the header files of the respective modules.
- Static const for any compile-time constants that are not integers or evaluated from expressions at compile-time, since these cannot be enums. These are defined in the header files as well.
- All method names in tests follow snake case, e.g. `can_hit_cache_with_alignment`, `can_init_arena`, `can_alloc_and_zero_arena`. This is to distinguish them from the actual functions in the codebase.

# Testing

- The following folder structure is used for testing in the `tests/` directory:
  - `unit` - contains the unit test files that run the functions in isolation
  - `integration/` - contains integration tests that run the internal parts of the renderer, such as the menu, and asserts that they work correctly in conjunction with the renderer
  - `e2e/` - few end-to-end tests that run the renderer with preconfigured settings and asserts via screenshot comparison
  - `scratch/` - a place for experiments and temporary tests that don't fit into the other categories; example: `ray.c` for testing different raylib related features
  - `standalone/` - contains tests that can be run independently of the main renderer, useful for testing specific features or functionalities without the full context of the renderer; example: `basics.c` for testing basic C features. These are intentionally not run as CMake tests. These are also to write smaller pieces of the implementation first that don't require any external libraries (i.e. raylib in this case), without having to compile the whole renderer.

# Tools

- Profiler: https://github.com/wolfpld/tracy/tree/master
- Debugger: https://github.com/EpicGamesExt/raddebugger and [debug.sh](debug.sh) script to gdb with the current build for e.g. segment faults or other issues.
- clang-tidy: Linter for displaying warnings and errors in the code, which can be run, https://clang.llvm.org/extra/clang-tidy/
