#include <iostream>

template <typename T>
int foo(const T& value) {
  return 0;
}

int foo(int value) { return value; }

template <typename Head, typename... Tail>
int foo(const Head& head, const Tail&... tail) {
  return foo(head) + foo(tail...);
}

int main() {
  std::cout << foo(1, "111", 3, 5, "234fsd") << std::endl;
  std::cout << foo("dsfa", 32434, 3.14, 'a');
}