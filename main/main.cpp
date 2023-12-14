// Copyright 2023 Dudchenko Olesya

#include <iostream>
#include "../lib_example/example.h"
#include "../lib_stack/stack.h"
#include "../lib_algorithms/algorithms.h"
#include "../lib_dsu/dsu.h"

int main() {
  int a = 1, b = 4; 
  float result;
  bool success = false;

  try {
      result = division(a, b);
      success = true;
  } catch (std::exception err) {
      std::cerr << err.what() << std::endl;
  }
  if (success) { printf("%d / %d = %.2f\n", a, b, result); success = false; }

  a = 1; b = 0;

  try {
      result = division(a, b);
      success = true;
  } catch (std::exception err) {
      std::cerr << err.what() << std::endl;
  }
  if (success) { printf("%d / %d = %.2f\n", a, b, result); success = false; }

  ExampleClass<int> obj(10);
  obj.setRandValues(-50, 30);
  std::cout << obj << std::endl;

  Stack<int> st(10);
  st.push(1);
  st.push(2);
  st.push(3);
  st.pop();
  st.push(4);
  st.print();


  return 0;
}
