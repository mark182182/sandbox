#include "arena.h"
#include <stdio.h>

static void exitWithMsg(char *msg) {
  fprintf(stderr, "Error: %s\n", msg);
  exit(1);
}

Arena Arena_Init(char *name, uint8_t *memory, size_t capacity) {
  if (!memory) {
    exitWithMsg("Memory cannot be null");
  }
  if (capacity == 0) {
    exitWithMsg("Capacity must be larger than 0");
  };

  Arena arena = {
      .name = name, .memory = memory, .capacity = capacity, .used = 0};
  return arena;
}

inline void *Arena_AllocAligned(Arena *arena, size_t size, size_t alignment) {
  uintptr_t currentAddr = (uintptr_t)(arena->memory + arena->used);

  // need to align the current address by zeroing out the least significant bits
  // this would round up
  uintptr_t alignedAddr =
      (currentAddr + (alignment - 1)) & ~(uintptr_t)(alignment - 1);

  size_t paddingSize = alignedAddr - currentAddr;
  size_t newUsedSize = arena->used + paddingSize + size;

  if (newUsedSize > arena->capacity) {
    printf_s("\nnewUsedSize\n");
    printf_s("%zu", newUsedSize);
    printf_s("\ncap\n");
    printf_s("%zu", arena->capacity);
    printf_s("\n");

    printf_s(arena->name);
    exitWithMsg("Cannot allocate memory, arena would be over capacity");
  }

  arena->used = newUsedSize;
  return (void *)alignedAddr;
}

/*
Rolls back the pointer to the original position, so the pre-allocated backing
byte storage can be reused.
*/
inline void Arena_Free(Arena *arena) { arena->used = 0; }