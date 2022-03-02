#ifndef INCLUDED__MCPP__STRING_HPP
#define INCLUDED__MCPP__STRING_HPP
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string.h>

class string {
private:
  char *str;
  int length;

public:
  string();
  string(const char *inputString);
  // Copy Konstruktor
  string(const string &other);
  // Move Konstruktor
  string(string &&other);
  void append(const char *inputString);
  char *data();
  int find(char c);
  void print();
  void clear();
  ~string();
};

#endif