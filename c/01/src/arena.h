#ifndef ARENA_H
#define ARENA_H

#include "stdint.h";

/**
 * ID-based memory arena for allocating objects in contiguous memory blocks
 * based on the object's size. Inspired by Ryan Fleury, Casey Muratori, Chris
 * Wellons and many others. `uint8_t` is used for byte level operations.
 */
typedef struct Arena {
  uint8_t base;
  uint8_t current;
  uint8_t end;
} Arena;

void ArenaInit(void);
void ArenaAlloc(void); // assert, if the memory was allocated successfully
void ArenaDealloc(
    void); // assert, if the memory was allocated successfully, make sure to
void ArenaGrow(void);   // cannot grow, if would be over capacity
void ArenaShrink(void); // without reallocation, cannot shrink, if size is at 0

/* How would Arena work together with the Arena Allocator ?
- Allocators should be separated by their lifetime:
  - one allocator would be used to store objects that need to be allocated in a
single frame and need to be released before the next frame; example: ?
  - one allocator would be used through multiple frames, but would get
deallocated at a given frame; example: cells that need to be used in multiple
frames, since the next frame would
  - others (list them)
- First, we need to initialize the arena using the ArenaAlloactor that would set
the size and capacity for the given type of object. The caller specifies the
size and the capacity. The allocation should be done in an aligned manner.
- Then usually the Arena would grow by one, when more objects need to be
allocated
- Dealloc would delete them all in one call at the end of the arena's lifetime

*/

#endif