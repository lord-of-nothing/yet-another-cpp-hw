#include <algorithm>
#include <cassert>
#include <iterator>
#include <numeric>
#include <gtest/gtest.h>

//  ================================================================================================

auto find(const int * array, std::size_t size, int key)
{
  auto result = false;

  if (size > 0)
  {
    auto l = 0uz, r = size - 1, m = 0uz;

    while (l < r)
    {
      array[m = std::midpoint(l, r)] < key ? l = m + 1 : r = m;
    }

    result = array[l] == key;
  }

  return result;
}

//  ================================================================================================

TEST(BinarySearchTest, FindsValue) {
  int array[]{ 1, 2, 3, 4, 5};
  EXPECT_EQ(find(array, std::size(array), 1), true);
}

int main()
{
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}