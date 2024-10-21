#include <algorithm>
#include <cassert>
#include <iterator>
#include <numeric>
#include <string>

//  ================================================================================================

template <typename T>
const T* binary_search(const T* array, std::size_t size, const T& key) {
  if (size > 0) {
    std::size_t l = 0;
    std::size_t r = size - 1;
    std::size_t m{};

    while (l < r) {
      array[m = std::midpoint(l, r)] < key ? l = m + 1 : r = m;
    }

    return (array[l] == key ? array + l : nullptr);
  }
  return nullptr;
}

//  ================================================================================================

int main() {
  const std::size_t size = 5;

  const int array[size]{1, 2, 3, 4, 5};

  assert(binary_search(array, size, 1) == array + 0);
  assert(binary_search(array, size, 2) == array + 1);
  assert(binary_search(array, size, 3) == array + 2);
  assert(binary_search(array, size, 4) == array + 3);
  assert(binary_search(array, size, 5) == array + 4);

  const std::string str_array[size]{"a", "aa", "b", "xxx", "yy"};
  assert(binary_search<std::string>(str_array, size, "aa") == str_array + 1);

  return 0;
}