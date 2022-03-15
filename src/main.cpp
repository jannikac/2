// Aufgabe 2a Blatt 2
#include "string.hpp"
#include <iostream>

int main() {
  // Test code:
  // string s2("asd");
  // s2.append("fgh");
  // s2.clear();
  // s2.append("xyz");
  // s2.print();

  // Copy konstruktor copy zuweisung?? move konstruktor??
  try {
    string test;
    test.find('a');
    test.print();
    test.append("a");

    string test2 = test;
    test.clear();
    test2.print();

    string test3(std::move(test2));
    string result = string("a") + string("b") + string("c");
    result.print();
  } catch (const std::exception &e) {
    std::cout << e.what() << std::endl;
  }

  return 0;
}