#ifndef ARENA_H
#define ARENA_H

#include "stdint.h";

/**
 * Memory arena for allocating objects in contiguous memory blocks
 * based on the object's size. Inspired by Ryan Fleury, Casey Muratori, Chris
 * Wellons and many others. `uint8_t` is used for byte level operations.
 *
 * NOTE: Usually the arenas are created at the Render level, so creating
 * ID-based arenas would be needed, if these need to be accessed from elsewhere;
 * example using enums for the type and an array to store the arenas, where the
 * index would be the value of the enum.
 */
typedef struct Arena {
  uint8_t base;
  uint8_t current;
  uint8_t end;
} Arena;

Arena Arena_Init(void);
/*
Make sure to use padding while allocating, as the allocating would require the
number of bytes skipped to ensure that the next allocated block is aligned to
the required alignment boundary (typically 4, 8, or 16 bytes, depending on the
platform and data type).
*/
void *
Arena_Alloc(Arena *arena); // assert, if the memory was allocated successfully
void Arena_Dealloc(Arena *arena); // assert, if the memory was allocated
                                  // successfully, make sure to

/* How would Arena work together with the Arena Allocator ?
- Allocators should be separated by their lifetime:
  - one allocator would be used to store objects that need to be allocated in a
single frame and need to be released before the next frame; example: ?
  - one allocator would be used through multiple frames, but would get
deallocated at a given frame; example: cells that need to be used in multiple
frames, since the next frame would
  - others (list them)
- First, we need to initialize the arena using the Arena_Alloc that would set
the size and capacity for the given type of object. The caller specifies the
size and the capacity. The allocation should be done in an aligned manner.
- Then usually objects would allocate
- Dealloc would delete them all in one call at the end of the arena's lifetime

*/

#endif