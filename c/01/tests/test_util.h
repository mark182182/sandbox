#ifndef TEST_UTIL
#define TEST_UTIL

#include <stdlib.h>
#include <stdio.h>

typedef struct TestCase {
  char *name;
  void (*testFn)();
} TestCase;

void runTests(char *fileName, TestCase tests[], size_t length) {
  printf("====Running tests in file %s====", fileName);
  for (int i = 0; i < length; i++) {
    printf("\n--Test case: %s--\n", tests[i].name);
    tests[i].testFn();
    printf("\n--Done: %s--\n", tests[i].name);
  }
  printf("===========DONE===========", fileName);
}

#endif