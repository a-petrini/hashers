#include <iostream>
#include <vector>
#include <string>

#include "configuration.h"
#include "utilbellebelle.hpp"

#include "benchmark/benchmark.h"

#include "zen_hashers.hpp"
#include "zcash_hashers.hpp"
#include "openssl_hashers.hpp"


std::vector<char> filebuffer;

static void one(benchmark::State& state) {
    const unsigned int N = state.range(0);
    std::vector<char> subvec;
    std::copy_n(std::begin(filebuffer), N, std::back_inserter(subvec));
    for (auto _ : state) {
        benchmark::DoNotOptimize(zen_sha1_hasher(subvec));
    }
    state.SetItemsProcessed(N*state.iterations());
}



int main(int argc, char** argv) {

    if (argc > 1)
        filebuffer = readBuffer(argv[1]);
    else {
        // Added a \n to be compliant with the content of test.txt
        const char * exampleData {"The quick brown fox jumps over the lazy dog\n"};
        std::copy(exampleData, exampleData + 44, std::back_inserter(filebuffer));
    }

    BENCHMARK(one)->RangeMultiplier(2)->Range(64, 64<<16);

    ::benchmark::Initialize(&argc, argv);
    ::benchmark::RunSpecifiedBenchmarks();
    ::benchmark::Shutdown();
}