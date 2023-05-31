#include "zcash_hashers_tests.hpp"
#include <cstring>
#include "common.h"
#include "benchmark/benchmark.h"

void zcash_sha1_perf(benchmark::State &state)
{
    const unsigned int N = state.range();
    std::vector<char> subvec(N);
    std::memcpy(subvec.data(), filebuffer.data(), N);
    for (auto _ : state)
    {
        auto hash = zcash_sha1_hasher(subvec);
        benchmark::DoNotOptimize(hash);
    }
    state.SetBytesProcessed(state.iterations() * N);
}

void zcash_sha256_perf(benchmark::State &state)
{
    const unsigned int N = state.range();
    std::vector<char> subvec(N);
    std::memcpy(subvec.data(), filebuffer.data(), N);
    for (auto _ : state)
    {
        auto hash = zcash_sha256_hasher(subvec);
        benchmark::DoNotOptimize(hash);
    }
    state.SetBytesProcessed(state.iterations() * N);
}

void zcash_sha512_perf(benchmark::State &state)
{
    const unsigned int N = state.range(0);
    std::vector<char> subvec(N);
    std::memcpy(subvec.data(), filebuffer.data(), N);
    for (auto _ : state)
    {
        auto hash = zcash_sha512_hasher(subvec);
        benchmark::DoNotOptimize(hash);
    }
    state.SetBytesProcessed(state.iterations() * N);
}
