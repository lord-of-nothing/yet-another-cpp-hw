#include <iostream>
#include <vector>

void selection_sort(std::vector<int>& vec) {
  for (size_t i = 0; i < std::size(vec) - 1; ++i) {
    size_t cur_min_idx = i;
    for (size_t j = i + 1; j < std::size(vec); ++j) {
      if (vec[j] < vec[cur_min_idx]) {
        cur_min_idx = j;
      }
    }
    std::swap(vec[i], vec[cur_min_idx]);
  }
}

int main() {
  size_t count = 0;
  std::cin >> count;
  std::vector<int> vec(count, 0);
  for (auto& elem : vec) {
    std::cin >> elem;
  }
  selection_sort(vec);
  for (const auto& elem : vec) {
    std::cout << elem << ' ';
  }
}