#ifndef STRING_HPP
#define STRING_HPP

class string {
private:
  char *str;

public:
  string();
  string(const char *inputString);
  void append(const char *inputString);
  char *data();
  int find(char c);
  void print();
  void clear();
  ~string();
};

#endif