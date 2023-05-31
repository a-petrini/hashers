#include "zcash_hashers_tests.hpp"
#include <cstring>
#include "common.h"
#include "benchmark/benchmark.h"

void zcash_sha1_perf(benchmark::State &state)
{
    const unsigned int N = state.range();
    for (auto _ : state)
    {
        auto hash = zcash_sha1_hasher(filebuffer.data(), N);
        benchmark::DoNotOptimize(hash);
    }
    state.SetBytesProcessed(state.iterations() * N);
}

void zcash_sha256_perf(benchmark::State &state)
{
    const unsigned int N = state.range();
    for (auto _ : state)
    {
        auto hash = zcash_sha256_hasher(filebuffer.data(), N);
        benchmark::DoNotOptimize(hash);
    }
    state.SetBytesProcessed(state.iterations() * N);
}

void zcash_sha512_perf(benchmark::State &state)
{
    const unsigned int N = state.range(0);
    for (auto _ : state)
    {
        auto hash = zcash_sha512_hasher(filebuffer.data(), N);
        benchmark::DoNotOptimize(hash);
    }
    state.SetBytesProcessed(state.iterations() * N);
}
