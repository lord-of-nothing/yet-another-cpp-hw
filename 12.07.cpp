#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

template <typename Collection>
std::string join(const Collection& data, const std::string& separator) {
  if (!data.size()) {
    return "";
  }

  std::ostringstream result;
  std::copy(std::begin(data), std::end(data) - 1,
            std::ostream_iterator<std::string>(result, separator.data()));
  result << *(std::end(data) - 1);
  return result.str();
}

int main() {
  std::vector<std::string> data = {"yet", "another", "example", "string"};
  std::string separator = " AAAA ";
  std::cout << join(data, separator) << std::endl;
}