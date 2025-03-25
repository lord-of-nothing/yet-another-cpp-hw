#include <iostream>
#include <string>

std::string compress(const std::string& str) {
    if (!str.size()) {
        return "";
    }

    std::string result;
    int cur_count = 1;
    for (size_t i = 1; i < str.size(); ++i) {
        if (str[i - 1] != str[i]) {
            result += str[i - 1] + std::to_string(cur_count);
            cur_count = 1;
        } else {
            ++cur_count;
        }
    }
    result += str.back() + std::to_string(cur_count);

    return result;
}

int main() {
    std::string origin = "aaabbcdddde";
    std::cout << compress(origin) << std::endl;
}