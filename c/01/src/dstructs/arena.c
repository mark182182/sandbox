#include "arena.h"
#include <stdio.h>
#include <string.h>

static void __ExitWithMsg(char *msg) {
  fprintf(stderr, "Error: %s\n", msg);
  exit(1);
}

static void __ExitWithArenaMsg(Arena *arena, char *msg) {
  fprintf(stderr, "Error: %s\n", msg);
  if (arena != NULL) {
    fprintf(stderr, "Arena was: %s, capacity: %zu, used: %zu\n", arena->name,
            arena->capacity, arena->used);
  }
  exit(1);
}

Arena Arena_Init(char *name, uint8_t *memory, size_t capacity) {
  if (!memory) {
    __ExitWithMsg("Memory cannot be null");
  }
  if (capacity == 0) {
    __ExitWithMsg("Capacity must be larger than 0");
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
    printf_s("Allocation would be over the limit");
    printf_s("\nWanted newUsedSize: %zu\n", newUsedSize);
    __ExitWithArenaMsg(arena,
                       "Cannot allocate memory, arena would be over capacity");
  }

  arena->used = newUsedSize;
  return (void *)alignedAddr;
}

inline void *Arena_AllocAlignedZeroed(Arena *arena, size_t size,
                                      size_t alignment) {
  void *ptr = Arena_AllocAligned(arena, size, alignment);
  if (ptr != NULL) {
    memset(ptr, 0, size);
  }
  return ptr;
}

/*
Rolls back the pointer to the original position, so the pre-allocated backing
byte storage can be reused.
*/
inline void Arena_Free(Arena *arena) { arena->used = 0; }
inline void Arena_FreeZeroed(Arena *arena) {
  arena->used = 0;
  if (arena->memory != NULL) {
    memset(arena->memory, 0, arena->capacity);
  }
}