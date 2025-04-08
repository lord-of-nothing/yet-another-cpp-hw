#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::vector<int>> CreatePascalsTriangle(size_t rows) {
  std::vector<std::vector<int>> result(rows, std::vector<int>(rows, 0));

  for (size_t i = 0; i < rows; ++i) {
    result[i][0] = 1;
  }

  for (size_t i = 0; i < rows; ++i) {
    for (size_t j = 1; j < i + 1; ++j) {
      result[i][j] = result[i - 1][j - 1] + result[i - 1][j];
    }
  }

  return result;
}

void PrintPascalsTriangle(size_t row_count) {
  auto data = CreatePascalsTriangle(row_count);
  size_t width =
      std::to_string(data[row_count - 1][data.back().size() / 2 + 1]).length();

  std::vector<std::string> rows;
  for (const auto& row : data) {
    std::ostringstream oss;
    for (const auto& value : row) {
      if (value == 0) {
        break;
      }
      oss << std::setw((width * 2) + 1) << value;
    }
    rows.push_back(oss.str());
  }

  size_t max_row = rows.back().length();
  for (const auto& row : rows) {
    int padding = (max_row - row.length()) / 2;
    std::cout << std::string(padding, ' ') << row << std::endl;
  }
}

int main() { PrintPascalsTriangle(10); }