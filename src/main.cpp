// Aufgabe 2a Blatt 2
#include "string.hpp"
#include <iostream>

int b() {
  string s("hallo ");
  char *data = s.data();
  s.append("Welt!");
  data[0] = 'H';
  s.print();
  return 0;
}

void print_string(string s) { s.print(); }

int main() {
  // std::cout << "hello world" << std::endl;
  // string s2("asd");
  // s2.append("fgh");
  // s2.clear();
  // s2.append("xyz");
  // s2.print();
  string test("test");
  print_string(test);
  test.print();

  // b();
}