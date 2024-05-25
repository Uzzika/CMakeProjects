// Copyright 2023 Dudchenko Olesya

#include <iostream>
#include "../lib_example/example.h"
#include "../lib_stack/stack.h"
#include "../lib_algorithms/algorithms.h"
#include "../lib_dsu/dsu.h"
#include "../lib_binary_tree/binTree.h"

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


  BinaryTree tree;
  tree.insert(5);
  tree.insert(3);
  tree.insert(7);
  tree.insert(2);
  tree.insert(4);
  tree.insert(6);
  tree.insert(8);

  std::cout << "BFS before removal: ";
  tree.BFS(printNode);
  std::cout << std::endl;

  Node* nodeToRemove = tree.find(3);
  tree.remove(nodeToRemove);

  std::cout << "BFS after removal: ";
  tree.BFS(printNode);
  std::cout << std::endl;

  return 0;
}
