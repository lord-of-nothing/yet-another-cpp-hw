#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> split(const std::string& str,
                               const std::string& delimiters) {
  std::vector<std::string> result;

  size_t last_split = 0;
  size_t cur_idx = str.find_first_of(delimiters, last_split);
  while (cur_idx != std::string::npos) {
    result.push_back(str.substr(last_split, cur_idx - last_split));
    last_split = cur_idx + 1;
    cur_idx = str.find_first_of(delimiters, last_split);
  }
  
  if (last_split < str.size()) {
    result.push_back(str.substr(last_split));
  }

  return result;
}

int main() {
    std::string data = "lorem ipsum\\dolor*sit)amet.";
    std::string delimiters = "*) .\\";

    std::vector<std::string> result = split(data, delimiters);
    std::cout << result.size() << std::endl;
    for (const auto& elem : result) {
        std::cout << elem << std::endl;
    }
}