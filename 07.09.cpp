#include <benchmark/benchmark.h>

class NonVirtual {
 public:
  __attribute__((noinline))void bar(int& start) {
    int b = 0;
    for (int i = start; i < start + 100; ++i) {
      b += i;
    }
    ++start;
  }
};

class Virtual {
 public:
  __attribute__((noinline))virtual void foo(int& start) {
    int a = 0;
    for (int i = start; i < start + 100; ++i) {
      a += i;
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
      c += i;
    }
    junk = 1;
    ++start;
  }
 private:
  int junk = 0;
};

static void BM_NonVirtual(benchmark::State& state) {
  NonVirtual* a = new NonVirtual;
  int start = 1;
  for (auto _ : state) {
    a->bar(start);
  }
  benchmark::DoNotOptimize(a);
}

static void BM_Virtual(benchmark::State& state) {
  int start = 1;
  Virtual* a = new ChildVirtual;
  for (auto _ : state) {
    a->foo(start);
  }
  benchmark::DoNotOptimize(a);
  delete a;
}

BENCHMARK(BM_NonVirtual);
BENCHMARK(BM_Virtual);

BENCHMARK_MAIN();
