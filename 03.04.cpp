#include <iostream>

class BaseLeft {
 public:
  virtual void foo() { std::cout << "first base class" << std::endl; }
};

class BaseRight {
 public:
  virtual void foo() { std::cout << "second base class" << std::endl; }
};

class DerivedWrong : public BaseLeft, public BaseRight {
 public:
  void foo() override { std::cout << "just derived!" << std::endl; }
};

class MiddleLeft : public BaseLeft {
 public:
  virtual void foo_left() = 0;

 private:
  void foo() { foo_left(); }
};

class MiddleRight : public BaseRight {
 public:
  virtual void foo_right() = 0;

 private:
  void foo() { foo_right(); }
};

class DerivedCorrectly : public MiddleLeft, public MiddleRight {
 public:
  void foo_left() override { std::cout << "derived left!" << std::endl; }
  void foo_right() override { std::cout << "derived right!" << std::endl; }
};

int main() {
  // суть проблемы:
  DerivedWrong derived_wrong;
  // мы не можем переопределить foo() обоих родительских методов по-отдельности
  BaseLeft* ba = &derived_wrong;
  BaseRight* bb = &derived_wrong;
  ba->foo();
  bb->foo();
  // и, как бы мы ни вызывали foo() у derived_wrong, мы попадём в один и тот же метод

  // решение --- промежуточные классы
  DerivedCorrectly derived_correctly;
  // теперь у нас есть foo_left и foo_right, переопределяющие foo() в BaseLeft и
  // BaseRight соответственно
  // и всё работает!
  derived_correctly.foo_left();
  derived_correctly.foo_right();
}