#include <iostream>
#include <vector>

void reverse(std::vector<int>& vec) {
  for (size_t i = 0; i < std::size(vec) / 2; ++i) {
    std::swap(vec[i], vec[std::size(vec) - i - 1]);
  }
}

int main() {
  size_t count = 0;
  std::cin >> count;
  std::vector<int> vec(count, 0);
  for (size_t i = 0; i < count; ++i) {
    std::cin >> vec[i];
  }

  reverse(vec);

  for (const auto& elem : vec) {
    std::cout << elem << ' ';
  }
}