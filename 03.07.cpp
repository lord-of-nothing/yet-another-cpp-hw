#include <cstdint>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class IPv4 {
 public:
  // давайте поверим, что значения корректные
  IPv4(uint8_t a, uint8_t b, uint8_t c, uint8_t d) : address_({a, b, c, d}) {}

  void change_address(uint8_t a, uint8_t b, uint8_t c, uint8_t d) {
    address_[0] = a;
    address_[1] = b;
    address_[2] = c;
    address_[3] = d;
  }

 private:
  std::vector<uint8_t> address_;

  friend std::ostream& operator<<(std::ostream& os, const IPv4& address);
};

std::ostream& operator<<(std::ostream& os, const IPv4& address) {
  for (size_t i = 0; i < 3; ++i) {
    os << static_cast<int>(address.address_[i]) << '.';
  }
  os << static_cast<int>(address.address_[3]);
  return os;
}

std::istream& operator>>(std::istream& is, IPv4& address) {
  std::vector<uint8_t> segments;
  std::string input;
  is >> input;
  std::stringstream ss(input);

  while (std::getline(ss, input, '.')) {
    segments.push_back(std::stoi(input));
  }
  if (segments.size() != 4) {
    is.setstate(std::ios::failbit);
  }
  address.change_address(segments[0], segments[1], segments[2], segments[3]);
  return is;
}

int main() {
  IPv4 a(192, 168, 0, 1);
  std::cout << a;
  std::cin >> a;
  std::cout << a;
}