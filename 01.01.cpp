#include <iostream>

// option zero
// вот эта штука, которую поддерживают некоторые компиляторы (g++, clang)
// вызовет функцию на старте программы
void on_startup() __attribute__((constructor));
void on_startup() { std::cout << "\tusing compiler-specific things\n"; }

// option one
// создаём глобальную переменную и присваиваем ей результат
// выполнения функции, в теле которой есть cout
int first_func() {
  std::cout << "somebody\n";
  return 42;
}

int first = first_func();

// option two
// создаём глобальный объект некоторого класса,
// в конструкторе которого есть cout
class Second {
 public:
  Second() { std::cout << "once told be\n"; }
  ~Second() {
    // option yet another one
    // ещё cout можно в деструктор засунуть
    std::cout << "\tinside destructor\n";
  }
};

Second second;

// option three
// внаглую вызываем cout и присваиваем результат его работы
// глобальной переменной
std::ostream& third = std::cout << "the world is gonna roll me\n";

// option final
// используем atexit(), чтобы вывод осуществился при завершении программы
auto final = std::atexit([]() { std::cout << "\tusing atexit()\n"; });

// option four
// return с подвохом
#define return                                            \
  std::cout << "i ain't the sharpest tool in the shed\n"; \
  return
int main() { return 0; }
