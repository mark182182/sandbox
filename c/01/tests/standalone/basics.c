#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

static void exitWithMsg(char *msg) {
  fprintf(stderr, "Error: %s\n", msg);
  exit(1);
}

// this should not display any warnings besides unused variables
void can_use_compile_time_constants() {
  printf("\n[can_use_compile_time_constants]\n");
  // compile time constants
  static const double FOO = 0.1234;
  static const int BAR = 1 << 3;
  static const int BAZ = 5;
  static const char *FOO_BAR = "foo_bar";

  // calculated
  static const double DIVIDED_FOO = FOO / BAR;

  printf("DIVIDED_FOO = %f\n", DIVIDED_FOO);
}

void can_report_memory_leaks() {
  printf("\n[can_report_memory_leaks]\n");

  char *leak = malloc(256);
  free(leak);
  printf("%s", leak); // use after free, should be reported by AddressSanitizer
}

int adder(int a, int b) { return a + b; }
int subt(int a, int b) { return a - b; }

int arithmetic(int (*op)(int a, int b)) {
  int a = 1;
  int b = 2;
  return op(a, b);
}

void can_use_function_ptrs() {
  printf("\n[can_use_function_ptrs]\n");
  int addRes = arithmetic(adder);
  int subtRes = arithmetic(subt);

  printf("Using adder function pointr: %d \n", addRes);
  printf("Using subt function pointr: %d \n", subtRes);
}

// reserve this much amount of memory upfront, would need to profile first how
// much more would be needed in the actual application, as this is only for
// demonstration purpose
static const size_t PERMANENT_STORAGE_SIZE = 32 * 1024 * 1024; // 32 MB
static const size_t FRAME_STORAGE_SIZE = 16 * 1024 * 1024;     // 16 MB

// backing memory byte storages for the arenas
uint8_t permanentStorage[PERMANENT_STORAGE_SIZE];
uint8_t frameStorage[FRAME_STORAGE_SIZE];

/**
 *
 * Inspired by Ryan Fleury's talk: Enter The Arena: Simplifying Memory
 * Management (2023)
 *
 * Since the memory is reserved upfront, the arena does not have to do this
 * itself. It just "distributes" the memory of the pre-allocated space.
 *
 * Initial arena with no allocations:
 * Capacity = 128 MB
 * [start]|---------------------|[capacity]
 *
 * Arena with one allocation:
 * Example: one allocation with 80MB (distributed to the caller) in
 * one call [start]|xxxxxxxxxxxxxx------|[capacity]
 *
 * When an arena is at capacity, it would be best to reserve and commit more
 * pages. See virtual address space for more information, if this is actually
 * needed.
 *
 *
 */
typedef struct Arena {
  uint8_t *memory; // the pointer to the backing memory storage,
  size_t capacity; // maximum possible memory to be allocated
  size_t used;     // the currently used memory
} Arena;

/**
 * Initial reservation with a backing byte storage as memory.
 */
Arena Arena_Init(uint8_t *memory, size_t size);
/**
 * "Bumps" the pointer forward and distributes the pre-allocated memory to the
 * caller. Will use padding to fill up to the specified boundary, e.g. 32
 * bytes in case of AVX-256 operations.
 *
 * Even though the padding bytes might be wasteful, this is still favorable due
 to better cache locality that adheres to the SIMD requirements.
 *
 * @param arena the arena to allocate from
 * @param size number of bytes to allocate
 * @param alignment alignment that should be the power of 2 (4, 8, 16, 32, etc.)
 * @return the pointer to allocated memory, or NULL if insufficient space

 */
void *Arena_AllocAligned(Arena *arena, size_t size, size_t alignment);
void *Arena_Alloc(Arena *arena, size_t size);
// frees all of the allocated memory at once
void Arena_Free(Arena *arena);

Arena Arena_Init(uint8_t *memory, size_t capacity) {
  if (!memory) {
    exitWithMsg("Memory cannot be null");
  }
  if (capacity == 0) {
    exitWithMsg("Capacity must be larger than 0");
  };

  Arena arena = {.memory = memory, .capacity = capacity, .used = 0};
  return arena;
}

void *Arena_AllocAligned(Arena *arena, size_t size, size_t alignment) {
  size_t currentAddr = (uintptr_t)(arena->memory + arena->used);

  // need to align the current address by zeroing out the least significant bits
  // this would round up
  uintptr_t alignedAddr = (size + alignment - 1) & ~(alignment - 1);

  size_t paddingSize = alignedAddr - currentAddr;
  size_t newUsedSize = arena->used + paddingSize + size;

  if (newUsedSize <= arena->capacity) {
    exitWithMsg("Cannot allocate memory, arena would be over capacity");
  }

  arena->used = newUsedSize;
  return (void *)alignedAddr;
}

/**
 * Same as Arena_AllocAligned, but without alignment.
 */
void *Arena_Alloc(Arena *arena, size_t size) {
  size_t *currentAddress = arena->memory + arena->used;

  // TODO: assert that the memory is not over capacity

  return 0;
}

/*
Rolls back the pointer to the original position, so the pre-allocated backing
byte storage can be reused.
*/
void Arena_Free(Arena *arena) { arena->used = 0; }

void can_use_arena_allocator() {
  printf("\n[can_use_arena_allocator]\n");

  Arena ar = Arena_Init(&permanentStorage, 1024);
  printf("\nArena used address: %zu\n", ar.used);

  void *aligned1 = Arena_AllocAligned(&ar, 8, 32);
  printf("\nArena used address: %zu\n", ar.used);

  void *aligned2 = Arena_AllocAligned(&ar, 32, 32);
  printf("\nArena used address: %zu\n", ar.used);

  void *aligned3 = Arena_AllocAligned(&ar, 64, 32);
  printf("\nArena used address: %zu\n", ar.used);

  void *aligned4 = Arena_AllocAligned(&ar, 14, 32);
  printf("\nArena used address: %zu\n", ar.used);

  Arena_Free(&ar);
  printf("\nArena used address: %zu\n", ar.used);
}

int main() {
  printf("-- Running basics test\n"
         "\tDown the yellow brick road\n"
         "\tThese would be multline strings,\n"
         "\tas C doesn't have string literal/text blocks\n");
  can_use_compile_time_constants();
  // can_report_memory_leaks();
  can_use_function_ptrs();
  can_use_arena_allocator();

  printf("-- Done\n");
  return 0;
}
