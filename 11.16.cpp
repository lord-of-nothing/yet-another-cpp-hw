#include <iostream>
#include <ranges>
#include <vector>

// views::istream
void test_istream() {
  // позволяет работать с потоком ввода, как с диапазоном (например, в range-based for)
  std::cout << "views::istream" << std::endl;

  std::cout << "Input some numbers, then finish the input: ";
  auto data = std::views::istream<int>(std::cin);

  // выводим эти числа, увеличенные на 1
  for (const auto& elem : data) {
    std::cout << elem + 1 << ' ';
  }
}

// views::counted
void test_counted() {
  // позволяет создать диапазон на фиксированное количество элементов
  std::cout << "views::counted" << std::endl;
  std::vector<int> arr = {1, 2, 3, 4, 5};

  // создаём view без первого и последнего элементов массива
  auto view = std::views::counted(arr.begin() + 1, arr.size() - 2);

  for (const auto& elem : view) {
    std::cout << elem << ' ';
  }
  std::cout << std::endl;

  // меняем значение в исходном векторе и снова смотрим view
  arr[1] = 666;
  for (const auto& elem : view) {
    std::cout << elem << ' ';
  }
  std::cout << std::endl << std::endl;
}

// views::join
void test_join() {
  // позволяет объединить несколько диапазонов в один
  std::cout << "views::join" << std::endl;
  std::vector<std::vector<int>> arr = {{1, 2, 3}, {4, 5, 6}};

  auto view = arr | std::views::join;
  for (const auto& elem : view) {
    std::cout << elem << ' ';
  }
  std::cout << std::endl << std::endl;
}

// views::stride
void test_stride() {
  // позволяет выбирать элементы в диапазоне с некоторым шагом
  std::cout << "views::stride" << std::endl;
  std::vector<int> arr = {1, 0, 2, 0, 3, 0, 4};

  // убираем нули, делая шаг равным 2
  auto view = arr | std::views::stride(2);
  for (const auto& elem : view) {
    std::cout << elem << ' ';
  }
  std::cout << std::endl << std::endl;
}

int main() {
  test_counted();
  test_join();
  test_stride();
  test_istream();
}