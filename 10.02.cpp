#include <iostream>
#include <vector>

void fill_vector(std::vector<int>& vec) {
  size_t current_capacity = vec.capacity();
  std::cout << "Starting capacity: " << vec.capacity() << std::endl;

  for (int i = 0; i < 50; ++i) {
    vec.push_back(i);
    if (vec.capacity() != current_capacity) {
      std::cout << "Capacity changed: from " << current_capacity << " to "
                << vec.capacity() << std::endl;
      current_capacity = vec.capacity();
    }
  }
  std::cout << std::endl;
}

void basic() {
  // смотрим, как изменяется capacity при добавлении новых элементов в
  // изначально пустой вектор
  std::cout << "\tEmpty vector without .reserve:" << std::endl;
  std::vector<int> a;
  fill_vector(a);
  // результат: сначала capacity увеличивается с 0 до 1, далее при необходимости
  // увеличения вектора -- удваивается
}

void with_reserve() {
  // смотрим, что проиходит с capacity, если начальное значение задано вручную
  std::cout << "\tEmpty vector with .reserve:" << std::endl;
  std::vector<int> a;
  a.reserve(7);
  fill_vector(a);
  // результат: аналогично предыдущему пункту
  // как только изначально заданной capacity перестаёт хватать, ёмкость
  // удваивается
}

void too_big() {
  // а если элементов слишком много?
  std::cout << "\tReally big vector" << std::endl;
  std::vector<double> a;
  try {
    a.resize(2000000000, 1.0);
  } catch (...) {
    std::cout << "Error on initial allocation" << std::endl;
    return;
  }
  std::cout << "Initial capacity: " << a.capacity() << std::endl;
  try {
    a.push_back(-1);
  } catch (const std::bad_alloc& e) {
    std::cout << "Exception while trying to extend vector: " << e.what() << std::endl;
    std::cout << "Vector capacity now: " << a.capacity() << std::endl;
    return;
  }
  std::cout << "Vector was not big enough((" << std::endl;
  // когда у ОС не хватает ресурсов на удваивание вместимости вектора, случается bad_alloc
}

int main() {
  basic();
  with_reserve();
  too_big();
}