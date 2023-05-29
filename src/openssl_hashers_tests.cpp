#include "openssl_hashers_tests.hpp"

#include "common.h"
#include "benchmark/benchmark.h"

void openssl_sha1_perf(benchmark::State& state) {
    const unsigned int N = state.range(0);
    std::vector<char> subvec;
    std::copy_n(std::begin(filebuffer), N, std::back_inserter(subvec));
    for (auto _ : state) {
        benchmark::DoNotOptimize(openssl_sha1_hasher(mdctx, subvec));
    }
    state.SetBytesProcessed(state.iterations() * state.range(0));
}

void openssl_sha256_perf(benchmark::State& state){
    const unsigned int N = state.range(0);
    std::vector<char> subvec;
    std::copy_n(std::begin(filebuffer), N, std::back_inserter(subvec));
    for (auto _ : state) {
        benchmark::DoNotOptimize(openssl_sha256_hasher(mdctx, subvec));
    }
    state.SetBytesProcessed(state.iterations() * state.range(0));
}

void openssl_sha512_perf(benchmark::State& state){
    const unsigned int N = state.range(0);
    std::vector<char> subvec;
    std::copy_n(std::begin(filebuffer), N, std::back_inserter(subvec));
    for (auto _ : state) {
        benchmark::DoNotOptimize(openssl_sha512_hasher(mdctx, subvec));
    }
    state.SetBytesProcessed(state.iterations() * state.range(0));
}
