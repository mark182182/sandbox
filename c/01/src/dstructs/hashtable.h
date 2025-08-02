#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "stdint.h"

typedef struct HashTable {
  // TODO: Implement this properly
  int *keys;
  int *values;
  uint8_t size;
} HashTable;

#endif