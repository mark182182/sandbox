#include <stdlib.h>
#include <stdio.h>

// this should not display any warnings besides unused variables
void can_use_compile_time_constants() {
  printf("\n[can_use_compile_time_constants]\n");
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
  printf("\n[can_report_memory_leaks]\n");

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
  printf("\n[can_use_function_ptrs]\n");

  int addRes = arithmetic(adder);
  int subtRes = arithmetic(subt);

  printf("Using adder function pointr: %d \n", addRes);
  printf("Using subt function pointr: %d \n", subtRes);
}

int main() {
  printf("-- Running basics test\n"
         "\tDown the yellow brick road\n"
         "\tThese would be easy multline strings,\n"
         "\tas C doesn't have string literal/text blocks\n");
  can_use_compile_time_constants();
  // can_report_memory_leaks();
  can_use_function_ptrs();

  printf("-- Done\n");
  return 0;
}
