#include <iostream>

class Cls {
 public:
  int get_value() const { return a; }
 private:
  int a = 0;
};

int main() {
  Cls object;
  std::cout << "Original value: " << object.get_value() << std::endl;

  std::bit_cast<int*>(&object)[0] = 42;
  std::cout << "After std::bit_cast: " << object.get_value() << std::endl;

  reinterpret_cast<int*>(&object)[0] = 666;
  std::cout << "After reinterpret_cast: " << object.get_value() << std::endl;
}
