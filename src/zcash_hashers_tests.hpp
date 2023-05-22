#pragma once

#include "zcash_hashers.hpp"

#include "benchmark/benchmark.h"

void zcash_sha1_perf(benchmark::State& state);
void zcash_sha256_perf(benchmark::State& state);
void zcash_sha512_perf(benchmark::State& state);