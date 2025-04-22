#include <iostream>
#include <random>
#include <thread>
#include <vector>

void job(std::atomic<int>& points_inside_global, const int points_cnt) {
  static thread_local std::mt19937 generator(std::random_device{}());
  std::uniform_real_distribution<double> distribution(-1, 1);

  int points_inside_local = 0;
  for (int i = 0; i < points_cnt; ++i) {
    double x = distribution(generator);
    double y = distribution(generator);
    if (x * x + y * y < 1) {
      ++points_inside_local;
    }
  }

  points_inside_global += points_inside_local;
}

int main() {
  const int kPointsPerThread = 1000000;
  const int kThreadCount = 10;

  int total = kPointsPerThread * kThreadCount;
  std::atomic<int> points_inside = 0;
  std::vector<std::thread> threads;

  for (int i = 0; i < kThreadCount; ++i) {
    threads.emplace_back(job, std::ref(points_inside), kPointsPerThread);
  }

  for (auto& t : threads) {
    t.join();
  }

  std::cout << points_inside * 4.0 / total;
}