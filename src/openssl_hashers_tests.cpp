#include "common.h"
#include "openssl_hashers_tests.hpp"
#include "benchmark/benchmark.h"

void openssl_sha1_perf(benchmark::State &state)
{
    static auto md{EVP_get_digestbyname("SHA1")};
    const unsigned int N = state.range();
    for (auto _ : state)
    {
        auto hash = openssl_digest(md, mdctx, filebuffer.data(), N);
        benchmark::DoNotOptimize(hash);
    }
    state.SetBytesProcessed(state.iterations() * N);
}

void openssl_sha256_perf(benchmark::State &state)
{
    static auto md{EVP_get_digestbyname("SHA256")};
    const unsigned int N = state.range();
    for (auto _ : state)
    {
        auto hash = openssl_digest(md, mdctx, filebuffer.data(), N);
        benchmark::DoNotOptimize(hash);
    }
    state.SetBytesProcessed(state.iterations() * N);
}

void openssl_sha512_perf(benchmark::State &state)
{
    static auto md{EVP_get_digestbyname("SHA512")};
    const unsigned int N = state.range();
    for (auto _ : state)
    {
        auto hash = openssl_digest(md, mdctx, filebuffer.data(), N);
        benchmark::DoNotOptimize(hash);
    }
    state.SetBytesProcessed(state.iterations() * N);
}
