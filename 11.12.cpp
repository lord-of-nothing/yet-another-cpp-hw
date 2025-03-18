#include <algorithm>
#include <iostream>
#include <vector>

// для красоты
void print_array(const std::vector<int>& arr) {
  for (const auto& value : arr) {
    std::cout << value << ' ';
  }
  std::cout << std::endl;
}

// std::count
void count() {
  std::cout << "std::count" << std::endl;
  std::vector<int> arr = {5, 5, 32, 453, 5};
  std::cout << "Demo array: ";
  print_array(arr);

  for (const auto& target : {5, 32, 0}) {
    int count = std::count(arr.begin(), arr.end(), target);
    std::cout << "value: " << target << ", count: " << count << std::endl;
  }

  std::cout << std::endl;
}

// std::mismatch
void mismatch() {
  std::cout << "std::mismatch" << std::endl;
  std::vector<int> arr1 = {1, 2, 3, 4, 5, 6, 7, 8};
  std::vector<int> arr2 = {1, 2, 3, 4, 6, 6, 7, 8};
  std::cout << "First array:  ";
  print_array(arr1);
  std::cout << "Second array: ";
  print_array(arr2);

  auto result =
      std::mismatch(arr1.begin(), arr1.end(), arr2.begin(), arr2.end());
  std::cout << "First mismatching elements: " << *result.first
            << " in arr1 and " << *result.second << " in arr2\n";
  std::cout << "Indices: " << std::distance(arr1.begin(), result.first)
            << " in arr1 and " << std::distance(arr2.begin(), result.second)
            << " in arr2\n";

  std::cout << std::endl;
}

// std::equal
void equal() {
  std::cout << "std::equal" << std::endl;
  std::vector<int> arr1 = {8, 800, 555};
  std::vector<int> arr2 = {8, 800, 555, 35};
  std::cout << "First array:  ";
  print_array(arr1);
  std::cout << "Second array: ";
  print_array(arr2);

  std::cout << "Are first three elements of arrays equal? ";
  std::cout << std::equal(arr1.begin(), arr1.end(), arr2.begin(),
                          arr2.end() - 1)
            << std::endl;

  std::cout << "Are last three elements of arrays equal? ";
  std::cout << std::equal(arr1.begin(), arr1.end(), arr2.begin() + 1,
                          arr2.end())
            << std::endl;

  std::cout << std::endl;
}

// std::search
void search() {
  std::cout << "std::search" << std::endl;
  std::vector<int> arr = {1, 0, 1, 1, 0, 1, 0, 1, 1};
  std::vector<int> target1 = {0, 1, 0};
  std::vector<int> target2 = {0, 0};
  std::cout << "Data: ";
  print_array(arr);
  std::cout << "First sequence: ";
  print_array(target1);
  std::cout << "Second sequence: ";
  print_array(target2);

  auto result1 =
      std::search(arr.begin(), arr.end(), target1.begin(), target1.end());
  std::cout << "Target1 found at index: " << std::distance(arr.begin(), result1)
            << std::endl;
  auto result2 =
      std::search(arr.begin(), arr.end(), target2.begin(), target2.end());
  if (result2 == arr.end()) {
    std::cout << "Target2 not found" << std::endl;
  }
  std::cout << std::endl;
}

// std::replace
void replace() {
  std::cout << "std::replace" << std::endl;
  std::vector<int> arr = {1, 1, 1, 2, 3, 4, 5};
  std::cout << "Before: ";
  print_array(arr);

  std::replace(arr.begin(), arr.end(), 1, 6);
  std::cout << "After (replace 1 with 6): ";
  print_array(arr);

  std::cout << std::endl;
}

// std::remove
void remove() {
  std::cout << "std::remove" << std::endl;
  std::vector<int> arr = {1, 0, 2, 0, 3, 0, 4, 0, 5};
  std::cout << "Before: ";
  print_array(arr);
  std::cout << "Size before: " << arr.size() << std::endl;

  auto result = std::remove(arr.begin(), arr.end(), 0);
  std::cout << "After (removed zeros): ";
  for (auto it = arr.begin(); it != result; ++it) {
    std::cout << *it << ' ';
  }
  std::cout << std::endl
            << "Size after: " << arr.size() << std::endl
            << std::endl;
  ;
}

// std::unique
void unique() {
  std::cout << "std::unique" << std::endl;
  std::vector<int> arr = {1, 1, 1, 2, 3, 3, 4, 4, 4, 4, 5, 5, 6};
  std::cout << "Before: ";
  print_array(arr);
  std::cout << "Size before: " << arr.size() << std::endl;

  auto result = std::unique(arr.begin(), arr.end());
  std::cout << "After: ";
  for (auto it = arr.begin(); it != result; ++it) {
    std::cout << *it << ' ';
  }
  std::cout << std::endl
            << "Size after: " << arr.size() << std::endl
            << std::endl;
  ;
}

// std::rotate
void rotate() {
  std::cout << "std::rotate" << std::endl;
  std::vector<int> arr = {1, 2, 3, 4, 5};
  std::cout << "Before: ";
  print_array(arr);

  std::rotate(arr.begin(), arr.begin() + 2, arr.end());

  std::cout << "After (left rotation 2): ";
  print_array(arr);

  std::cout << std::endl;
}

// std::partition
void partition() {
  std::cout << "std::partition" << std::endl;
  std::vector<int> arr = {1, -1, 2, -2, 3, -3, 4};
  std::cout << "Before: ";
  print_array(arr);

  auto result = std::partition(arr.begin(), arr.end(), [](int x) { return x < 0; });

  std::cout << "After (partition by sign): ";
  print_array(arr);
  std::cout << "Index of first non-negative: " << std::distance(arr.begin(), result) << std::endl; 

  std::cout << std::endl;
}

// std::nth_element
void nth_element() {
  std::cout << "std::nth_element" << std::endl;
  std::vector<int> arr = {1, 6, 7, 2, 3, 5, 9, 4, 8};
  std::cout << "Before: ";
  print_array(arr);

  std::nth_element(arr.begin(), arr.begin() + arr.size() / 2, arr.end());
  std::cout << "After (partition by middle element): ";
  print_array(arr);
}

int main() {
  count();
  mismatch();
  equal();
  search();
  replace();
  remove();
  unique();
  rotate();
  partition();
  nth_element();
}