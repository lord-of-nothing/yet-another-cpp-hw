#include <gtest/gtest.h>

#include <algorithm>
#include <cassert>
#include <iterator>
#include <numeric>

//  ================================================================================================

auto find(const int* array, std::size_t size, int key) {
  auto result = false;

  if (size > 0) {
    auto l = 0uz, r = size - 1, m = 0uz;

    while (l < r) {
      array[m = std::midpoint(l, r)] < key ? l = m + 1 : r = m;
    }

    result = array[l] == key;
  }

  return result;
}

//  ================================================================================================

class BinarySearchTest : public testing::Test {
 protected:
  int array[5]{1, 2, 3, 4, 5};
};

TEST_F(BinarySearchTest, ExistingValue) {
  EXPECT_EQ(find(array, std::size(array), 1), true);
  EXPECT_EQ(find(array, std::size(array), 4), true);
}

TEST_F(BinarySearchTest, NonexistingValue) {
  EXPECT_EQ(find(array, std::size(array), -1), false);
  EXPECT_EQ(find(array, std::size(array), 666), false);
}

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}