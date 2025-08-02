#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "test_util.h"

// this should not display any warnings besides unused variables
void can_use_compile_time_constants() {
  // compile time constants
  static const double FOO = 0.1234;
  static const int BAR = 1 << 3;
  static const int BAZ = 5;
  static const char *FOO_BAR = "foo_bar";

  // calculated
  static const double DIVIDED_FOO = FOO / BAR;

  printf("DIVIDED_FOO = %f\n", DIVIDED_FOO);
}

void can_report_memory_leaks() {
  char *leak = malloc(256);
  free(leak);
  printf("%s", leak); // use after free, should be reported by AddressSanitizer
}

int adder(int a, int b) { return a + b; }
int subt(int a, int b) { return a - b; }

int arithmetic(int (*op)(int a, int b)) {
  int a = 1;
  int b = 2;
  return op(a, b);
}

void can_use_function_ptrs() {
  int addRes = arithmetic(adder);
  int subtRes = arithmetic(subt);

  printf("Using adder function pointr: %d \n", addRes);
  printf("Using subt function pointr: %d \n", subtRes);
}

void can_use_snprintf() {
  char *textToFmt = "[some text]";
  float floatToFmt = 0.1234F;

  char *format = "This is %s: %0.3f";

  char formattedTxt[64];

  snprintf(formattedTxt, sizeof(formattedTxt), format, textToFmt, floatToFmt);

  assert(formattedTxt == "This is [some text]: 0.123");
}

int main() {
  printf("-- Running basics test\n"
         "\tDown the yellow brick road\n"
         "\tThese would be multline strings,\n"
         "\tas C doesn't have string literal/text blocks\n");

  // can_report_memory_leaks();
  TestCase tests[] = {{.name = "can_use_compile_time_constants",
                       .testFn = can_use_compile_time_constants},
                      {.name = "can_use_function_ptrs", can_use_function_ptrs},
                      {.name = "can_use_snprintf", can_use_snprintf}};

  int testsLength = sizeof(tests) / sizeof(tests[0]);
  runTests(__FILE__, tests, testsLength);
  return 0;
}
