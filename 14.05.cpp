#include <chrono>
#include <future>
#include <iostream>
#include <random>
#include <string>
#include <thread>

int really_heavy_calculation() {
  using namespace std::chrono_literals;

  static thread_local std::mt19937 generator(std::random_device{}());
  std::uniform_int_distribution<int> distribution(-100, 100);

  std::this_thread::sleep_for(6s);
  return distribution(generator);
}

void job(const int thread_id, std::shared_future<int> sf) {
  int result = sf.get();
  std::string str = "thread " + std::to_string(thread_id) + " got value " +
                    std::to_string(result) + '\n';

  std::cout << str;
}

int main() {
  std::future<int> f = std::async(std::launch::async, really_heavy_calculation);
  std::shared_future<int> sf = f.share();

  std::jthread t1(job, 0, sf);
  std::jthread t2(job, 1, sf);
}