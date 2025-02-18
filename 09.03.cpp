#include <cassert>
#include <functional>
#include <iostream>
#include <vector>

namespace test {
std::vector<int> data = {666};
}

class Scope_Guard {
 public:
  // считаем, что функция отката ничего не принимает и ничего не возвращает
  Scope_Guard(std::function<void()> rollback) : rollback_(rollback) {}

  void disable() noexcept { is_active = false; }

  ~Scope_Guard() noexcept {
    if (is_active) {
      rollback_();
    }
  }

 private:
  std::function<void()> rollback_;
  bool is_active = true;
};

void A() { test::data.push_back(666); }

void reverse_A() { test::data.pop_back(); }

void B_bad() { throw std::exception(); }

void B_good() {}

void foo() {
  A();
  Scope_Guard guard(reverse_A);
  B_bad();
}

void bar() {
  A();
  Scope_Guard guard(reverse_A);
  B_good();
  guard.disable();
}

int main() {
  // добавляем элемент в "глобальный" вектор и удаляем его, если
  // было выброшено исключение
  // начальный размер вектора равен 1

  // исключение произошло
  try {
    foo();
  } catch (...) {
    std::cout << "Vector size: " << test::data.size() << std::endl;
  }

  // исключений не было
  bar();
  std::cout << "Vector size: " << test::data.size() << std::endl;
}