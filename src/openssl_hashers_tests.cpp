#include "openssl_hashers_tests.hpp"

#include "common.h"
#include <cstring>
#include "benchmark/benchmark.h"

void openssl_sha1_perf(benchmark::State &state)
{
    const unsigned int N = state.range();
    std::vector<char> subvec(N);
    std::memcpy(subvec.data(), filebuffer.data(), N);
    auto md{EVP_get_digestbyname("SHA1")};
    for (auto _ : state)
    {
        auto hash = openssl_sha1_hasher(md, mdctx, subvec);
        benchmark::DoNotOptimize(hash);
    }
    state.SetBytesProcessed(state.iterations() * state.range(0));
}

void openssl_sha256_perf(benchmark::State &state)
{
    const unsigned int N = state.range();
    std::vector<char> subvec(N);
    std::memcpy(subvec.data(), filebuffer.data(), N);
    auto md{EVP_get_digestbyname("SHA256")};
    for (auto _ : state)
    {
        auto hash = openssl_sha256_hasher(md, mdctx, subvec);
        benchmark::DoNotOptimize(hash);
    }
    state.SetBytesProcessed(state.iterations() * state.range(0));
}

void openssl_sha512_perf(benchmark::State &state)
{
    const unsigned int N = state.range();
    std::vector<char> subvec(N);
    std::memcpy(subvec.data(), filebuffer.data(), N);
    auto md{EVP_get_digestbyname("SHA512")};
    for (auto _ : state)
    {
        auto hash = openssl_sha512_hasher(md, mdctx, subvec);
        benchmark::DoNotOptimize(hash);
    }
    state.SetBytesProcessed(state.iterations() * state.range(0));
}
