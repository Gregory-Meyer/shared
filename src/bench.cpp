#include "vec_wrapper.h"

#include <chrono>
#include <vector>

#include <benchmark/benchmark.h>

static void bm_push_back_c(benchmark::State &state) {
    Vec vec("./libvecc.so");

    for (auto _ : state) {
        vec.push_back(0);
        benchmark::ClobberMemory();
    }
}
BENCHMARK(bm_push_back_c);

static void bm_push_back_cxx(benchmark::State &state) {
    Vec vec("./libveccxx.so");

    for (auto _ : state) {
        vec.push_back(0);
        benchmark::ClobberMemory();
    }
}
BENCHMARK(bm_push_back_cxx);

static void bm_push_back_stdlib(benchmark::State &state) {
    std::vector<int> vec;

    for (auto _ : state) {
        vec.push_back(0);
        benchmark::ClobberMemory();
    }
}
BENCHMARK(bm_push_back_stdlib);

BENCHMARK_MAIN();
