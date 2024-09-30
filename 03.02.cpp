#include <cmath>
#include <iostream>
#include <vector>

class Triangle {
 public:
  Triangle() = delete;
  Triangle(double a, double b, double c) : a_(a), b_(b), c_(c) {}

  double get_perimeter() const { return a_ + b_ + c_; }

  double get_area() const {
    double p = get_perimeter() / 2;
    return std::sqrt(p * (p - a_) * (p - b_) * (p - c_));
  }

  std::vector<double> get_sides() const { return std::vector{a_, b_, c_}; }

 private:
  double a_;
  double b_;
  double c_;
};

class Square {
 public:
  Square() = delete;
  Square(double side) : side_(side) {}

  double get_perimeter() const { return side_ * 4; }

  double get_area() const { return side_ * side_; }

  double get_side() const { return side_; }

 private:
  double side_;
};

class Circle {
 public:
  Circle() = delete;
  Circle(double radius) : radius_(radius) {}

  double get_perimeter() const { return 2 * kPi * radius_; }

  double get_area() const { return kPi * radius_ * radius_; }

  double get_radius() const { return radius_; }

 private:
  double radius_;
  constexpr static const double kPi = 3.14159;
};

int main() {
  double a, b, c;
  std::cout << "Triangle sides: ";
  std::cin >> a >> b >> c;
  Triangle triangle(a, b, c);
  std::cout << "Triangle perimeter: " << triangle.get_perimeter() << std::endl;
  std::cout << "Triangle area: " << triangle.get_area() << std::endl;

  std::cout << "Square side: ";
  std::cin >> a;
  Square square(a);
  std::cout << "Square perimeter: " << square.get_perimeter() << std::endl;
  std::cout << "Square area: " << square.get_area() << std::endl;

  std::cout << "Circle radius: ";
  std::cin >> b;
  Circle circle(b);
  std::cout << "Circle perimeter: " << circle.get_perimeter() << std::endl;
  std::cout << "Circle area: " << circle.get_area() << std::endl;
}