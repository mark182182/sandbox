#ifndef HASH_H
#define HASH_H

/*
 * Slightly modified djb2 hashing function by Daniel J.Bernstein, see
 * http://www.cse.yorku.ca/~oz/hash.html
 */
unsigned long hash(unsigned char *str);

#endif