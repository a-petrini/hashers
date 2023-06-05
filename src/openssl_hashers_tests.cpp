#include "common.h"
#include "openssl_hashers_tests.hpp"
#include "benchmark/benchmark.h"

void openssl_sha1_perf(benchmark::State &state)
{
    static auto md{EVP_get_digestbyname("SHA1")};

    const size_t kDigestLength{static_cast<size_t>(EVP_MD_size(md))};
    EVP_DigestInit_ex2(mdctx, md, nullptr); // Already implies a reset - Only first one requires the md
    

    const unsigned int N = state.range();
    for (auto _ : state)
    {
        std::vector<unsigned char> output(kDigestLength);
        EVP_DigestInit_ex2(mdctx, nullptr, nullptr); // Already implies a reset
        EVP_DigestUpdate(mdctx, filebuffer.data(), N);
        EVP_DigestFinal_ex(mdctx, output.data(), nullptr);
        benchmark::DoNotOptimize(output);
    }
    state.SetBytesProcessed(state.iterations() * N);
}

void openssl_sha256_perf(benchmark::State &state)
{
    static auto md{EVP_get_digestbyname("SHA256")};

    const size_t kDigestLength{static_cast<size_t>(EVP_MD_size(md))};
    EVP_DigestInit_ex2(mdctx, md, nullptr); // Already implies a reset - Only first one requires the md

    const unsigned int N = state.range();
    for (auto _ : state)
    {
        std::vector<unsigned char> output(kDigestLength);
        EVP_DigestInit_ex2(mdctx, nullptr, nullptr); // Already implies a reset
        EVP_DigestUpdate(mdctx, filebuffer.data(), N);
        EVP_DigestFinal_ex(mdctx, output.data(), nullptr);
        benchmark::DoNotOptimize(output);
    }
    state.SetBytesProcessed(state.iterations() * N);
}

void openssl_sha512_perf(benchmark::State &state)
{
    static auto md{EVP_get_digestbyname("SHA512")};

    const size_t kDigestLength{static_cast<size_t>(EVP_MD_size(md))};
    EVP_DigestInit_ex2(mdctx, md, nullptr); // Already implies a reset - Only first one requires the md

    const unsigned int N = state.range();
    for (auto _ : state)
    {
        std::vector<unsigned char> output(kDigestLength);
        EVP_DigestInit_ex2(mdctx, nullptr, nullptr); // Already implies a reset
        EVP_DigestUpdate(mdctx, filebuffer.data(), N);
        EVP_DigestFinal_ex(mdctx, output.data(), nullptr);
        benchmark::DoNotOptimize(output);
    }
    state.SetBytesProcessed(state.iterations() * N);
}
