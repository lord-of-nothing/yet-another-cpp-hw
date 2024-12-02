#include <iostream>

// с выражение свёртки
template <typename... Args>
std::size_t GetTotalSize(const Args&... args) {
  return (sizeof args + ...);
}

// без выражения свёртки
std::size_t GetTotalSizeNoFold() {
  return 0;
}

template <typename T>
std::size_t GetTotalSizeNoFold(const T& arg) {
  return sizeof arg;
}

template <typename T, typename... Args>
std::size_t GetTotalSizeNoFold(const T& first, const Args&... rest) {
  return sizeof first + GetTotalSizeNoFold(rest...);
}

int main() {
  std::cout << GetTotalSize(3.14, 'a', 666) << std::endl;
  std::cout << GetTotalSizeNoFold('a', 666, 3.14) << std::endl;
}