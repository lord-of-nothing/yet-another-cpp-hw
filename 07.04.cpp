#include <iostream>
#include <limits>
#include <vector>
#include <variant>
#include <optional>

int main() {
  // bad_alloc
  // невозможность выделить запрашиваемую память (например, её недостаточно)
  try {
    int* a = new int[99999999999];
    delete[] a;
  } catch (const std::bad_alloc& e){
    std::cout << "caught bad_alloc\n";
    std::cout << e.what() << "\n\n";
  }

  // bad_variant_access
  // выбрасывает std::get, если значения запрашиваемого типа нет в variant
  try {
    std::variant<int, double> var;
    var = 3.14;
    std::cout << std::get<int>(var);
  } catch (const std::bad_variant_access& e) {
    std::cout << "caught bad_variant_access\n";
    std::cout << e.what() << "\n\n";
  }

  // bad_optional_access
  // возникает при попытке получения значения optional, у которого значения нет
  try {
    std::optional<double> op;
    std::cout << op.value();
  } catch (const std::bad_optional_access& e) {
    std::cout << "caught bad_optional_access\n";
    std::cout << e.what() << "\n\n";
  }

  // std::length_error
  // возникает при попытке превысить допустимый размер контейнера
  try {
    std::vector<int> v;
    std::cout << v.max_size() << " is maximum vector<int> size\n";
    std::cout << std::numeric_limits<long long>::max() << " is attempted size\n";
    v.resize(std::numeric_limits<long long>::max());
  } catch (const std::length_error& e) {
    std::cout << "caught length_error\n";
    std::cout << e.what() << "\n\n";
  }

  // std::out_of_range
  // выбрасывается at() при попытке выхода за границы вектора
  try {
    std::vector<int> v{1, 2, 3};
    std::cout << v.at(3);
  } catch (const std::out_of_range& e) {
    std::cout << "caught out_of_range\n";
    std::cout << e.what();
  }
}