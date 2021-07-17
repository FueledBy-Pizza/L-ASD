
#include "zlasdtest/test.hpp"
#include "zmytestex5/test.hpp"
#include <iostream>

int main() {
  bool c;
  std::cout << "Lasd Libraries 2020" << std::endl << "Pick a choice: (1 lasdtest, 0 mytest)\t";
  std::cin >> c;
  if(c) lasdtest();
  else mytest();
  return 0;
}
