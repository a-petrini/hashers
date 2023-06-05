#include "common.h"
#include "openssl_hashers_tests.hpp"
#include "benchmark/benchmark.h"

void openssl_sha1_perf(benchmark::State &state)
{

    const unsigned int N = state.range();
    for (auto _ : state)
    {
        auto hash = openssl_sha1_hasher(filebuffer.data(), N);
        benchmark::DoNotOptimize(hash);
    }
    state.SetBytesProcessed(state.iterations() * N);

}

void openssl_sha256_perf(benchmark::State &state)
{
    const unsigned int N = state.range();
    for (auto _ : state)
    {
        auto hash = openssl_sha256_hasher(filebuffer.data(), N);
        benchmark::DoNotOptimize(hash);
    }
    state.SetBytesProcessed(state.iterations() * N);
}

void openssl_sha512_perf(benchmark::State &state)
{
    const unsigned int N = state.range();
    for (auto _ : state)
    {
        auto hash = openssl_sha512_hasher(filebuffer.data(), N);
        benchmark::DoNotOptimize(hash);
    }
    state.SetBytesProcessed(state.iterations() * N);
}
