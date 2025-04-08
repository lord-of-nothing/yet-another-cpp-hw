#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::string Transform(const std::vector<uint8_t>& numbers) {
  std::ostringstream output;
  for (const auto& num : numbers) {
    output << std::hex << std::uppercase << static_cast<int>(num);
  }
  return output.str();
}

int main() {
  std::vector<uint8_t> example = {0xBA, 0xAD};
  std::cout << Transform(example) << std::endl;

  std::vector<uint8_t> data = {222, 173};
  std::cout << Transform(data) << std::endl;
}