#include <iostream>
#include <string>
#include <typeinfo>
#include "factorial.h"
using namespace std;

int main()
{
  int num = 0;
  std::cout << "Please type in a number: ";
  std::cin >> num;
  std::string numAsString = std::to_string(num);
  std::cout << "Given number ("<< num << ") original type: " << typeid(num).name() << endl;
  std::cout << "Double: " << num * 2 << endl;
  std::cout << "Factorial: " << factorial(num) << endl;
  std::cout << "Given number (" << numAsString << ") displayed as: " << typeid(numAsString).name();
  return 0;
}