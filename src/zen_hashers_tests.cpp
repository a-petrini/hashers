#include "zen_hashers_tests.hpp"
#include <cstring>
#include "common.h"
#include "benchmark/benchmark.h"

void zen_sha1_perf(benchmark::State &state)
{
    const unsigned int N = state.range();
    std::vector<char> subvec(N);
    std::memcpy(subvec.data(), filebuffer.data(), N);
    for (auto _ : state)
    {
        auto hash = zen_sha1_hasher(subvec);
        benchmark::DoNotOptimize(hash);
    }
    state.SetBytesProcessed(state.iterations() * N);
}

void zen_sha256_perf(benchmark::State &state)
{
    const unsigned int N = state.range();
    std::vector<char> subvec(N);
    std::memcpy(subvec.data(), filebuffer.data(), N);
    for (auto _ : state)
    {
        auto hash = zen_sha256_hasher(subvec);
        benchmark::DoNotOptimize(hash);
    }
    state.SetBytesProcessed(state.iterations() * N);
}

void zen_sha512_perf(benchmark::State &state)
{
    const unsigned int N = state.range();
    std::vector<char> subvec(N);
    std::memcpy(subvec.data(), filebuffer.data(), N);
    for (auto _ : state)
    {
        auto hash = zen_sha512_hasher(subvec);
        benchmark::DoNotOptimize(hash);
    }
    state.SetBytesProcessed(state.iterations() * N);
}
