#include <cmath>
#include <iostream>
#include <numbers>
#include <vector>

class Shape {
 public:
  virtual double get_perimeter() const = 0;
  virtual double get_area() const = 0;
  virtual ~Shape() {};
};

class Polygon : public Shape {
 public:
  Polygon(std::initializer_list<double> sides) : sides_(sides) {}

  double get_perimeter() const override {
    double result = 0;
    for (const auto& elem : sides_) {
      result += elem;
    }
    return result;
  }

  ~Polygon() = default;

 protected:
  std::vector<double> sides_;
};

class Rectangle : public Polygon {
 public:
  Rectangle(double a, double b) : Polygon({a, b, a, b}) {}

  double get_area() const override { return sides_[0] * sides_[1]; }
};

class Square : public Rectangle {
 public:
  Square(double a) : Rectangle(a, a) {}
};

class Triangle : public Polygon {
 public:
  Triangle(double a, double b, double c) : Polygon({a, b, c}) {}

  double get_area() const override {
    double p = get_perimeter() / 2;
    return std::sqrt(p * (p - sides_[0]) * (p - sides_[1]) * (p - sides_[2]));
  }

 private:
  double a_;
  double b_;
  double c_;
};

class Ellipse : public Shape {
 public:
  Ellipse(double a, double b) : a_(std::max(a, b)), b_(std::min(a, b)) {}

  double get_perimeter() const override {
    double tmp = 3 * (a_ - b_) * (a_ - b_) / (a_ + b_) / (a_ + b_);
    return std::numbers::pi * (a_ + b_) * (1 + tmp / (10 + std::sqrt(4 - tmp)));
  }

  double get_area() const override { return std::numbers::pi * a_ * b_; }

  ~Ellipse() = default;

 private:
  double a_;
  double b_;
};

class Circle : public Ellipse {
 public:
  Circle(double r) : Ellipse(r, r) {}
};

int main() {
  double a = 0, b = 0, c = 0;
  std::cout << "Rectangle sides: ";
  std::cin >> a >> b;
  Rectangle rectangle(a, b);
  std::cout << "Rectangle perimeter: " << rectangle.get_perimeter() << std::endl;
  std::cout << "Rectangle area: " << rectangle.get_area() << std::endl;

  std::cout << "\nSquare side: ";
  std::cin >> a;
  Square square(a);
  std::cout << "Square perimeter: " << square.get_perimeter() << std::endl;
  std::cout << "Square area: " << square.get_area() << std::endl;

  std::cout << "\nTriangle sides: ";
  std::cin >> a >> b >> c;
  Triangle triangle(a, b, c);
  std::cout << "Triangle perimeter: " << triangle.get_perimeter() << std::endl;
  std::cout << "Triangle area: " << triangle.get_area() << std::endl;

  std::cout << "\nEllipse semiaxes: ";
  std::cin >> a >> b;
  Ellipse ellipse(a, b);
  std::cout << "Ellipse perimeter (approximate): " << ellipse.get_perimeter() << std::endl;
  std::cout << "Ellipse area: " << ellipse.get_area() << std::endl;

  std::cout << "\nCircle radius: ";
  std::cin >> a;
  Circle circle(a);
  std::cout << "Circle perimeter: " << circle.get_perimeter() << std::endl;
  std::cout << "Circle area: " << circle.get_area() << std::endl;
}