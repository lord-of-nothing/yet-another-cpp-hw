#include <iostream>
#include <string>
#include <vector>

std::string longest_palindrome(const std::string& str) {
  size_t len = str.size();
  std::vector<std::vector<bool>> dp(len, std::vector<bool>(len, false));
  int max_len = 1;
  size_t max_start = 0;

  for (size_t i = 0; i < len; ++i) {
    dp[i][i] = true;
  }

  for (size_t i = 0; i < len - 1; ++i) {
    if (str[i] == str[i + 1]) {
      dp[i][i + 1] = true;
      if (max_len < 2) {
        max_len = 2;
        max_start = i;
      }
    }
  }

  for (size_t cur_size = 3; cur_size <= len; ++cur_size) {
    for (size_t i = 0; i < len - cur_size + 1; ++i) {
      size_t j = i + cur_size - 1;
      dp[i][j] = dp[i + 1][j - 1] && str[i] == str[j];
      if (dp[i][j] && max_len < cur_size) {
        max_len = cur_size;
        max_start = i;
      } 
    }
  }

  return str.substr(max_start, max_len);
}

int main() {
    std::cout << longest_palindrome("sahararahnide") << std::endl;
    std::cout << longest_palindrome("aaaa") << std::endl;
    std::cout << longest_palindrome("cbbd") << std::endl;
    std::cout << longest_palindrome("XYZ") << std::endl;
}