#include "dstructs/arena.h"
#include <assert.h>
#include "test_util.h"

uint8_t test_storage[1024];
char *name = "test-arena";
uint8_t *memory = &test_storage;
size_t capacity = 64;
size_t alignment = DEFAULT_ARENA_ALIGNMENT;

typedef struct Foo {
  int bar;
  int baz;
} Foo;

// since there are 2 int fields in foo
int FOO_SIZE = 8;

void can_init_arena() {
  assert(sizeof(Foo) == FOO_SIZE);

  Arena arena = Arena_Init(name, memory, capacity);

  assert(&arena != NULL);
  assert(arena.name == name);
  assert(arena.memory == memory);
  assert(arena.capacity == capacity);
}

void can_alloc_arena_with_padding() {
  Arena arena = Arena_Init(name, memory, capacity);

  uint8_t foosCount = 2;
  // there aren't really any other ways to get the number of elements in the
  // array, other than this or using macros this cannot be extracted to a
  // function, since foos would be pass as a pointer and not as the array, so
  // sizeof(foos) would be the size of the pointer in that case
  Foo *foos = Arena_AllocAligned(&arena, sizeof(Foo) * foosCount, alignment);

  assert(foos != NULL);
  assert(&foos[0] != NULL);
  assert(&foos[1] != NULL);

  assert(sizeof(foos) * sizeof(foos[0]) / alignment == foosCount);

  foos[0].bar = 1;
  foos[1].bar = 2;

  foos[0].bar = foos[0].bar + 3;
  foos[1].bar = foos[1].bar + 4;

  assert(foos[0].bar == 4);
  assert(foos[1].bar == 6);

  // the the addresses for the two foos should only take up half the padding (so
  // 16 bytes)
  printf("foos[0]: %d\n", &foos[0]);
  printf("foos[1]: %d\n", &foos[1]);

  uintptr_t currentAddr = (uintptr_t)(arena.memory + arena.used);
  uintptr_t alignedAddr =
      (currentAddr + (alignment - 1)) & ~(uintptr_t)(alignment - 1);
  size_t paddingSize = alignedAddr - currentAddr;

  printf("currentAddr: %d\n", currentAddr);
  printf("alignedAddr: %d\n", alignedAddr);
  printf("paddingSize: %d\n", paddingSize);

  /*
  foo[0] is at the first address, for 8 bytes (2 int fields in Foo)
  foo[1] starts after foo's 8 bytes of data
  since we reserve sizeof(Foo) * 2, there will be 16 bytes of data + the padding

  This means that our arena will start with the 16 bytes of actual data for the
  2 Foo objects and have 16 bytes of padding in order to be in the 32 byte
  alignment.

  Since we substract the first object's address from the last one, that means we
  would get the size of Foo.

  and since pointer size also differs based on the hardware, we have to use
  uintptr_t for safety rather than uint8_t or something like that

  Since pointer size differs based on the hardware etc., so it's advised to cast
  to uintptr_t for safety rather than uint8_t or similar.
  */
  uintptr_t lastFooAddr = (uintptr_t)&foos[1];
  uintptr_t firstFooAddr = (uintptr_t)&foos[0];
  uintptr_t startingAddr = lastFooAddr - firstFooAddr - sizeof(Foo);

  printf("startingAddr: %d", startingAddr);
  assert(startingAddr == 0);
}

void can_alloc_and_zero_arena() {
  Arena arena = Arena_Init(name, memory, capacity);
  Foo *foos = Arena_AllocAlignedZeroed(&arena, sizeof(Foo) * 2, alignment);

  printf("\narena.used: %d\n", arena.used);
  assert(arena.used == alignment);

  // all foos should be zerod out
  for (int i = 0; i < sizeof(foos) * sizeof(foos[0]) / alignment; i++) {
    printf("\n&foos[i]: %d\n", foos[i].bar);
    assert(foos[i].bar == 0);
    assert(foos[i].baz == 0);
  }
}

void can_free_arena() {
  Arena arena = Arena_Init(name, memory, capacity);
  Foo *foos = Arena_AllocAligned(&arena, sizeof(Foo) * 2, alignment);
  printf("\n%zu\n", sizeof(foos) * sizeof(foos[0]) / alignment);

  for (int i = 0; i < sizeof(foos) * sizeof(foos[0]) / alignment; i++) {
    foos[i].bar = 1;
    foos[i].baz = 1;
  }

  printf("arena.used: %d", arena.used);
  assert(arena.used == alignment);

  Arena_FreeZeroed(&arena);
  assert(arena.used == 0);

  // all foos should be zerod out
  for (int i = 0; i < sizeof(foos) * sizeof(foos[0]) / alignment; i++) {
    printf("\n&foos[i]: %d\n", foos[i].bar);
    assert(foos[i].bar == 0);
    assert(foos[i].baz == 0);
  }
}

int main() {
  TestCase tests[] = {
      {.name = "can_init_arena", .testFn = can_init_arena},
      {.name = "can_alloc_arena_with_padding_used",
       .testFn = can_alloc_arena_with_padding},
      {.name = "can_alloc_and_zero_arena", .testFn = can_alloc_and_zero_arena},
      {.name = "can_free_arena", .testFn = can_free_arena}};

  int testsLength = sizeof(tests) / sizeof(tests[0]);
  runTests(__FILE__, tests, testsLength);
}