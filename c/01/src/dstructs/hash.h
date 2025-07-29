#ifndef HASH_H
#define HASH_H

typedef enum HashAlgos { DJB2 } HashAlgos;

/*
 * Slightly modified djb2 hashing function by Daniel J.Bernstein, see
 * http://www.cse.yorku.ca/~oz/hash.html
 */
unsigned long Hash_DJB2(unsigned char *str);

#endif