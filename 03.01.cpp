#include <iostream>
#include <vector>

struct Rectangle {
  int x = 0;
  int y = 0;
  int width = 0;
  int height = 0;
};

int get_intersection_area(const std::vector<Rectangle>& rectangles) {
  if (!std::size(rectangles)) {
    return 0;
  }

  Rectangle intersection = rectangles[0];
  for (size_t i = 1; i < std::size(rectangles); ++i) {
    int x = std::max(intersection.x, rectangles[i].x);
    int y = std::max(intersection.y, rectangles[i].y);
    int width = std::min(intersection.x + intersection.width,
                         rectangles[i].x + rectangles[i].width) -
                x;
    int height = std::min(intersection.y + intersection.height,
                          rectangles[i].y + rectangles[i].height) -
                 y;
    if (width <= 0 || height <= 0) {
      return 0;
    }

    intersection.x = x;
    intersection.y = y;
    intersection.width = width;
    intersection.height = height;
  }
  return intersection.width * intersection.height;
}

int main() {
  size_t count = 0;
  std::cin >> count;
  std::vector<Rectangle> rectangles(count, Rectangle());
  for (auto& elem : rectangles) {
    std::cin >> elem.x >> elem.y >> elem.width >> elem.height;
  }
  std::cout << get_intersection_area(rectangles);
}