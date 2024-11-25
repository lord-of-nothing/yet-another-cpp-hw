#include <cmath>
#include <utility>
#include <variant>
#include <iostream>

std::variant<std::monostate, double, std::pair<double, double>>
SolveQuadraticEquation(double a, double b, double c) {
  std::variant<std::monostate, double, std::pair<double, double>> result;
  double d = b * b - 4 * a * c;
  if (d == 0.0) {
    result = -b / (2 * a);
  } else if (d > 0) {
    double droot = std::sqrt(d);
    result.emplace<std::pair<double, double>>((-b - droot) / (2 * a),
                                              (-b + droot) / (2 * a));
  } else {
    result = std::monostate();
  }
  return result;
}

int main() {
  double a, b, c;
  std::cout << "Enter coeffs: ";
  std::cin >> a >> b >> c;
  auto result = SolveQuadraticEquation(a, b, c);
  switch (result.index()) {
    case 0:
      std::cout << "no real solutions";
      break;
    case 1:
      std::cout << "one solution: " << std::get<1>(result);
      break;
    case 2:
      auto answers = std::get<2>(result);
      std::cout << "two solutions: " << answers.first << ' ' << answers.second;
  }
}