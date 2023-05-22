#pragma once

#include "zen_hashers.hpp"

#include "benchmark/benchmark.h"

void zen_sha1_perf(benchmark::State& state);
void zen_sha256_perf(benchmark::State& state);
void zen_sha512_perf(benchmark::State& state);