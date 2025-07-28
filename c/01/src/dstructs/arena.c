#include "arena.h"

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

/*
Rolls back the pointer to the original position, so the pre-allocated backing
byte storage can be reused.
*/
void Arena_Free(Arena *arena) { arena->used = 0; }