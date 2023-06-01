#include "common.h"
#include "zen_hashers_tests.hpp"
#include "benchmark/benchmark.h"

void zen_sha1_perf(benchmark::State &state)
{
    const unsigned int N = state.range();
    for (auto _ : state)
    {
        auto hash = zen_sha1_hasher(filebuffer.data(), N);
        benchmark::DoNotOptimize(hash);
    }
    state.SetBytesProcessed(state.iterations() * N);
}

void zen_sha256_perf(benchmark::State &state)
{
    const unsigned int N = state.range();
    for (auto _ : state)
    {
        auto hash = zen_sha256_hasher(filebuffer.data(), N);
        benchmark::DoNotOptimize(hash);
    }
    state.SetBytesProcessed(state.iterations() * N);
}

void zen_sha512_perf(benchmark::State &state)
{
    const unsigned int N = state.range();
    for (auto _ : state)
    {
        auto hash = zen_sha512_hasher(filebuffer.data(), N);
        benchmark::DoNotOptimize(hash);
    }
    state.SetBytesProcessed(state.iterations() * N);
}
