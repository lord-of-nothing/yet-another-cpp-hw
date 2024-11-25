#include <iostream>
#include <optional>
#include <string>

class Person {
 public:
  Person(const std::string& name, const std::string& surname)
      : name(name), surname(surname) {};
  void setAge(int value) { age = value; }
  void setHometown(const std::string& value) { hometown = value; }
  std::string get_name() const { return name; }
  std::string get_surname() const { return surname; }
  std::optional<int> get_age() const { return age; }
  std::optional<std::string> get_hometown() { return hometown; }

  std::string toString() const {
    std::string result = name + ' ' + surname;
    if (age) {
      result += " " + std::to_string(age.value()) + " y.o.";
    }
    if (hometown) {
      result += " of " + hometown.value();
    }
    return result;
  }

 private:
  std::string name;
  std::string surname;
  std::optional<int> age;
  std::optional<std::string> hometown;
};

int main() {
  Person p("Voryn", "Dagoth");
  std::cout << p.toString() << std::endl;
  p.setHometown("Kogoruhn");
  std::cout << p.toString() << std::endl;
  p.setAge(3900);
  std::cout << p.toString() << std::endl;
}
