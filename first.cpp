#include "calib/add.h"
#include "mult/mul.h"
#include <iostream>

int main() {
  int sum = add(2, 3);
  std::cout << "first.cpp is running: sum = " << sum << std::endl;
  int res = mul(2, 3);
  std::cout << "first.cpp is running: res = " << res << std::endl;

  return 0;
}

// 14:05 :02