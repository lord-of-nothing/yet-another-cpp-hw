#include <iostream>
#include <numeric>
#include <vector>

// для красоты
void print_array(const std::vector<int>& arr) {
  for (const auto& value : arr) {
    std::cout << value << ' ';
  }
  std::cout << std::endl;
}

// std::accumulate
void accumulate(const std::vector<int>& arr) {
  std::cout << "std::accumulate" << std::endl;

  int result_full = std::accumulate(arr.begin(), arr.end(), 0);
  std::cout << "Result (sum of all elements): " << result_full << std::endl;
  int result_three = std::accumulate(arr.begin(), arr.begin() + 3, 0);
  std::cout << "Result (sum of first three elements): " << result_three
            << std::endl
            << std::endl;
}

// std::partial_sum
void partial_sum(const std::vector<int>& arr) {
  std::cout << "std::partial_sum" << std::endl;
  std::vector<int> result(arr.size());

  std::partial_sum(arr.begin(), arr.end(), result.begin());
  std::cout << "Result (prefix sums): ";
  print_array(result);
  std::cout << std::endl;
}

// std::adjacent_difference
void adjacent_difference(const std::vector<int>& arr) {
  std::cout << "std::adjacent_difference" << std::endl;
  std::vector<int> result(arr.size());

  std::adjacent_difference(arr.begin(), arr.end(), result.begin());
  std::cout << "Result (differences between adjacent elements): ";
  print_array(result);
  std::cout << std::endl;
}

// std::inner_product
void inner_product() {
  std::cout << "std::inner_product" << std::endl;
  std::vector<int> v1 = {2, 1};
  std::vector<int> v2 = {6, -3};
  std::cout << "First vector: ";
  print_array(v1);
  std::cout << "Second vector: ";
  print_array(v2);

  int result = std::inner_product(v1.begin(), v1.end(), v2.begin(), 0);
  std::cout << "Scalar product: " << result << std::endl;
}

int main() {
  std::cout << "Array for first three tests: ";
  std::vector<int> arr = {-5, 4, -3, 2, -1, 0, 1, -2, 3, -4, 5};
  print_array(arr);
  std::cout << std::endl;

  accumulate(arr);
  partial_sum(arr);
  adjacent_difference(arr);
  inner_product();
}