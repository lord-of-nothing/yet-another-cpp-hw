#include <iostream>
#include <string>
#include <vector>

uint8_t hex_to_int(char digit) {
    if (digit >= '0' && digit <= '9') {
        return digit - '0';
    }
    digit = std::toupper(digit);
    if (digit >= 'A' && digit <= 'F') {
        return digit - 'A' + 10;
    }
    throw std::invalid_argument("Invalid hexadecimal character");
}

std::vector<uint8_t> hex_split(const std::string& digits) {
    std::vector<uint8_t> result;
    result.reserve(digits.size());

    for (int i = 0; i < digits.size(); i += 2) {
        result.push_back(hex_to_int(digits[i]) * 16 + hex_to_int(digits[i + 1]));
    }

    return result;
}

int main() {
    std::string origin = "BAAD";
    auto result = hex_split(origin);
    for (const auto& elem : result) {
        std::cout << static_cast<int>(elem) << std::endl;
    }
}