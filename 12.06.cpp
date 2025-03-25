#include <iostream>
#include <sstream>
#include <string>

std::string capitalize(const std::string& text) {
    std::string result;
    result.reserve(text.size());
    bool capitalize_next = true;
    for (const char c : text) {
        if (std::isalpha(c) && capitalize_next) {
            result += std::toupper(c);
            capitalize_next = false;
        } else if (std::isalpha(c)) {
            result += std::tolower(c);
        } else {
            result += c;
            capitalize_next = std::isspace(c) || std::ispunct(c);
        }
    }
    return result;
}

int main() {
    std::string origin = "bAra BADa bAsTu";
    std::cout << capitalize(origin) << std::endl;
}