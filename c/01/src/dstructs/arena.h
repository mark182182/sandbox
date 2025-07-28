#ifndef ARENA_H
#define ARENA_H

#include <stdint.h>;

// reserve this much amount of memory upfront, would need to profile first how
// much more would be needed in the actual application, as this is only for
// demonstration purpose
static const size_t PERMANENT_STORAGE_SIZE = 32 * 1024 * 1024; // 32 MB
static const size_t FRAME_STORAGE_SIZE = 16 * 1024 * 1024;     // 16 MB

// backing memory byte storages for the arenas
uint8_t permanentStorage[PERMANENT_STORAGE_SIZE];
uint8_t frameStorage[FRAME_STORAGE_SIZE];

static const uint8_t DEFAULT_ARENA_ALIGNMENT = 32;

/**
 *
 * Inspired by Ryan Fleury's talk: Enter The Arena: Simplifying Memory
 * Management (2023) and also Casey Muratori, Chris Wellons and others.
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
 * NOTE: Usually the arenas are created at the Render level, so creating
 * ID-based arenas would be needed, if these need to be accessed from elsewhere;
 * example using enums for the type and an array to store the arenas, where the
 * index would be the value of the enum.
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

#endif