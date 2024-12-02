#include <algorithm>
#include <cassert>
#include <iterator>
#include <numeric>
#include <utility>
#include <vector>
#include <gtest/gtest.h>

//  ================================================================================================

void sort(std::vector<int>& vector, std::size_t left, std::size_t right) {
  for (auto i = left + 1; i < right; ++i) {
    for (auto j = i; j > left; --j) {
      if (vector[j - 1] < vector[j]) {
        std::swap(vector[j], vector[j - 1]);
      }
    }
  }
}

//  ================================================================================================

void merge(std::vector<int>& vector, std::size_t left, std::size_t middle,
           std::size_t right) {
  std::vector<int> copy(right - left, 0);

  for (auto i = left, j = middle; auto& element : copy) {
    if (i < middle && ((j < right && vector[i] >= vector[j]) || j == right)) {
      element = vector[i++];
    } else {
      element = vector[j++];
    }
  }

  for (auto i = 0uz; auto element : copy) {
    vector[left + i++] = element;
  }
}

//  ================================================================================================

void split(std::vector<int>& vector, std::size_t left, std::size_t right) {
  if (right - left <= 64) {
    sort(vector, left, right);
  } else {
    auto middle = std::midpoint(left, right);

    split(vector, left, middle);
    split(vector, middle, right);
    merge(vector, left, middle, right);
  }
}

//  ================================================================================================

void timsort(std::vector<int>& vector, std::size_t left, std::size_t right) {
  split(vector, left, right);
}

//  ================================================================================================

class TimsortTest : public testing::Test {
 protected:
  TimsortTest() {
    std::ranges::iota(vector, 1);
  }

  std::vector<int> vector{1'000, 0};
};

TEST_F(TimsortTest, IsSorted) {
  timsort(vector, 0, std::size(vector));
  EXPECT_TRUE(std::ranges::is_sorted(vector, std::ranges::greater()));
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}