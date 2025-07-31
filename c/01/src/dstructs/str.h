#ifndef STR_H
#define STR_H

#include <stdlib.h>;
#include "dstructs/arena.h";

/**
 * The capacity is available via the arena.
 */
typedef struct Str {
  char *chars;
  size_t length;
  Arena *arena;
} Str;

/*
only in case it's actually needed
Str_UTF8Decode();
Str_UTF8Encode();
*/

#endif