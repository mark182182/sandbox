#ifndef ARENA_H
#define ARENA_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * Reserves memory for the lifetime of the application
 *
 * NOTE: initial estimate without measurement, increase as needed
 */
static const size_t PERMANENT_STORAGE_SIZE = 24 * 1024 * 1024;
/**
 * Need storage for all of Cells2D's fields, for which the formula is currently:
 * CELL_COUNT * numberOfFields * numberOfArenas
 *
 *
 * Example, if CELL_COUNT is 11.520:
 *
 * CELL_COUNT * (cells * positionX * positionY * colors) * (firstGenArena +
 * secondGenArena) = 11.520 * (4*4*4*4) * 2 = 737.280 or 720 KB (this is not
 * correct, see below)
 *
 * For some reason the actual used memory for one Cells2D will be: 195.840 (so
 * 196.608, 192KB), which would be 393.216 (384 KB)
 */
static const size_t GEN_STORAGE_SIZE = 192 * 1024;

// NOTE: initial estimate without measurement for the lifetime for the 2D and 3D
// modes, increase as needed
static const size_t MODE_STORAGE_SIZE = 16 * 1024 * 1024;

// NOTE: initial estimate without measurement, increase as needed
static const size_t FRAME_STORAGE_SIZE = 8 * 1024 * 1024; // 8 MB

// backing memory storages for the arenas in bytes
static uint8_t permanentStorage[PERMANENT_STORAGE_SIZE];
static uint8_t firstGenStorage[GEN_STORAGE_SIZE];
static uint8_t secondGenStorage[GEN_STORAGE_SIZE];
static uint8_t modeArenaStorage[MODE_STORAGE_SIZE];
static uint8_t frameStorage[FRAME_STORAGE_SIZE];

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
  char *name;
  uint8_t *memory; // the pointer to the backing memory storage,
  size_t capacity; // maximum possible memory to be allocated
  size_t used;     // the currently used memory
} Arena;

/**
 * Initial reservation with a backing byte storage as memory.
 */
extern inline Arena Arena_Init(char *name, uint8_t *memory, size_t capacity);
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
extern inline void *Arena_AllocAligned(Arena *arena, size_t size, size_t alignment);
extern inline void *Arena_AllocAlignedZeroed(Arena *arena, size_t size,
                                      size_t alignment);
// frees all of the allocated memory at once
extern inline void Arena_Free(Arena *arena);
extern inline void Arena_FreeZeroed(Arena *arena);

#endif