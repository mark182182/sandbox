int factorial(int num) {
  int buf = 1;
  for (int i = 1; i <= num; i++) {
    buf *= i;
  }
  return buf;
}