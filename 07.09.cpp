#include <benchmark/benchmark.h>

class Testing {
 public:

  void bar() {
    int b = 0;
    for (int i = 0; i < 1000; ++i) {
      benchmark::DoNotOptimize(b += i);
    }
  }
  virtual void foo() {
    int a = 0;
    for (int i = 0; i < 1000; ++i) {
      benchmark::DoNotOptimize(a += i);
    }
  }

  virtual ~Testing() = default;
};

Testing t;

static void BM_NonVirtual(benchmark::State& state) {
  for (auto _ : state) {
    t.bar();
  }
}

static void BM_Virtual(benchmark::State& state) {
  for (auto _ : state) {
    t.foo();
  }
}

BENCHMARK(BM_NonVirtual);
BENCHMARK(BM_Virtual);

BENCHMARK_MAIN();

/* хотелось бы сделать выводы, но значения при каждом запуске
 * получаются разными, причём быстрее оказывается то один, то другой вариант
 * и разница почти всегда мала
 * разобраться, с чем это может быть связано, пока не получилось */