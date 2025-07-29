#include "hash.h"

unsigned long Hash_DJB2(unsigned char *str) {
  unsigned long hash = 5381;

  int c;

  while (c = *str++) {
    hash = ((hash << 5) + hash) + c;
  }
  return hash;
}