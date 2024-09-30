#include <iostream>
#include <utility>
#include <numeric>
#include <vector>

bool IsArmstrong(int number, std::vector<int64_t>& powers) {
  int cur_sum = 0;
  const int original = number;
  while (number > 0) {
    cur_sum += powers[number % 10];
    number /= 10;
  }
  return original == cur_sum;
}

std::vector<int> GetArmstrong(int max_number) {
  std::vector<int64_t> powers(10, 0);
  std::iota(powers.begin(), powers.end(), 0);

  std::vector<int> result;
  int64_t limit = 10;
  for (int cur_num = 1; cur_num < max_number; ++cur_num) {
    if (cur_num == limit) {
      limit *= 10;
      for (size_t j = 0; j < powers.size(); ++j) {
        powers[j] = powers[j] * j;
      }
    }
    if (IsArmstrong(cur_num, powers)) {
      result.push_back(cur_num);
    }
  }

  return result;
}

std::vector<int> GetFibonacci(int max_number) {
  std::vector<int> result;
  result.push_back(0);
  result.push_back(1);
  int current_index = 2;
  while (true) {
    int next_fib = result[current_index - 1] + result[current_index - 2];
    if (next_fib >= max_number) {
      break;
    }
    result.push_back(next_fib);
    ++current_index;
  }
  return result;
}

bool IsAbundant(int number) {
  int64_t div_sum = 1;
  int cur_div = 2;
  while (cur_div * cur_div < number) {
    if (number % cur_div == 0) {
      div_sum += cur_div + number / cur_div;
    }
    if (div_sum > number) {
      return true;
    }
    ++cur_div;
  }
  if (cur_div * cur_div == number) {
    div_sum += cur_div;
  }
  return div_sum > number;
}

std::vector<int> GetAbundant(int max_number) {
  std::vector<int> result;
  for (int i = 1; i < max_number; ++i) {
    if (IsAbundant(i)) {
      result.push_back(i);
    }
  }
  return result;
}

int64_t GetDivisorSum(int number) {
  int64_t div_sum = 1;
  int cur_div = 2;
  while (cur_div * cur_div < number) {
    if (number % cur_div == 0) {
      div_sum += cur_div + number / cur_div;
    }
    ++cur_div;
  }
  if (cur_div * cur_div == number) {
    div_sum += cur_div;
  }
  return div_sum;
}

std::vector<std::pair<int, int>> GetAmicable(int64_t max_number) {
  std::vector<std::pair<int, int>> result;

  for (int i = 1; i < max_number; ++i) {
    int64_t div_sum = GetDivisorSum(i);
    if (div_sum <= i || div_sum > max_number) {
      continue;
    }
    if (i == GetDivisorSum(div_sum)) {
      result.emplace_back(i, div_sum);
    }
  }
  return result;
}

/* бонус: подсчёт избыточных и дружественных чисел можно объединить,
 * чтобы не считать сумму собственных делителей дважды,
 * так как меньшее из чисел в паре дружественных точно избыточное
 * (ещё можно считать ту сумму единожды и где-нибудь хранить) */
void GetAbundantAmicable(int64_t max_number, std::vector<int>& abundant,
                         std::vector<std::pair<int, int>>& amicable) {
  for (int i = 1; i < max_number; ++i) {
    int64_t div_sum = GetDivisorSum(i);
    if (div_sum > i) {
      abundant.push_back(i);
    }
    if (div_sum <= i || div_sum > max_number) {
      continue;
    }
    if (i == GetDivisorSum(div_sum)) {
      amicable.emplace_back(i, div_sum);
    }
  }
}

int main() {
  // на числах больше максимума int'а работать точно не будет
  // на меньших должно, но может быть долго
  int max_number = 0;
  std::cin >> max_number;

  std::vector<int> armstrong = GetArmstrong(max_number);
  std::cout << "Armstrong numbers: ";
  for (const auto& elem : armstrong) {
    std::cout << elem << ' ';
  }
  std::cout << '\n';

  std::vector<int> fibonacci = GetFibonacci(max_number);
  std::cout << "Fibonacci numbers: ";
  for (const auto& elem : fibonacci) {
    std::cout << elem << ' ';
  }
  std::cout << '\n';

  std::vector<int> abundant = GetAbundant(max_number);
  std::cout << "Abundant numbers: ";
  for (const auto& elem : abundant) {
    std::cout << elem << ' ';
  }
  std::cout << '\n';

  std::vector<std::pair<int, int>> amicable = GetAmicable(max_number);
  std::cout << "Amicable numbers: \n";
  for (const auto& elem : amicable) {
    std::cout << elem.first << ' ' << elem.second << '\n';
  }
}