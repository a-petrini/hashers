#include "zcash_hashers_tests.hpp"

#include "common.h"
#include "benchmark/benchmark.h"

void zcash_sha1_perf(benchmark::State& state) {
    const unsigned int N = state.range(0);
    std::vector<char> subvec;
    std::copy_n(std::begin(filebuffer), N, std::back_inserter(subvec));
    for (auto _ : state) {
        benchmark::DoNotOptimize(zcash_sha1_hasher(subvec));
    }
    state.SetBytesProcessed(state.iterations() * state.range(0));
}

void zcash_sha256_perf(benchmark::State& state){
    const unsigned int N = state.range(0);
    std::vector<char> subvec;
    std::copy_n(std::begin(filebuffer), N, std::back_inserter(subvec));
    for (auto _ : state) {
        benchmark::DoNotOptimize(zcash_sha256_hasher(subvec));
    }
    state.SetBytesProcessed(state.iterations() * state.range(0));
}

void zcash_sha512_perf(benchmark::State& state){
    const unsigned int N = state.range(0);
    std::vector<char> subvec;
    std::copy_n(std::begin(filebuffer), N, std::back_inserter(subvec));
    for (auto _ : state) {
        benchmark::DoNotOptimize(zcash_sha512_hasher(subvec));
    }
    state.SetBytesProcessed(state.iterations() * state.range(0));
}
