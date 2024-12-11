#include <benchmark/benchmark.h>

class NonVirtual {
 public:
  __attribute__((noinline))void bar(int& start) {
    int b = 0;
    for (int i = start; i < start + 100; ++i) {
      benchmark::DoNotOptimize(b += i);
    }
    ++start;
  }
};

class Virtual {
 public:
  __attribute__((noinline))virtual void foo(int& start) {
    int a = 0;
    benchmark::DoNotOptimize(a);
    for (int i = start; i < start + 100; ++i) {
      benchmark::DoNotOptimize(a += i);
    }
    ++start;
  }

  virtual ~Virtual() = default;
};

class ChildVirtual : public Virtual {
 public:
  void foo(int& start) override {
    int c = 0;
    for (int i = start; i < start + 100; ++i) {
      benchmark::DoNotOptimize(c += i);
    }
    junk = 1;
    ++start;
  }
 private:
  int junk = 0;
};

static void BM_NonVirtual(benchmark::State& state) {
  NonVirtual a;
  int start = 1;
  for (auto _ : state) {
    a.bar(start);
  }
}

static void BM_Virtual(benchmark::State& state) {
  int start = 0;
  ChildVirtual cv;
  cv.foo(start);
  benchmark::DoNotOptimize(cv);

  Virtual a;
  for (auto _ : state) {
    a.foo(start);
  }
}

BENCHMARK(BM_NonVirtual);
BENCHMARK(BM_Virtual);

BENCHMARK_MAIN();
