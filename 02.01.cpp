#include <iostream>

void Categorize(char character) {
  switch (character) {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      std::cout << "digit\n";
      break;
    case '+':
    case '-':
    case '*':
    case '/':
      std::cout << "operator\n";
      break;
    case '(':
    case ')':
      std::cout << "parenthesis\n";
      break;
    default:
      std::cout << "not recognized\n";
  }
}

int main() {
  char character;
  while (std::cin >> character) {
    Categorize(character);
  }
}