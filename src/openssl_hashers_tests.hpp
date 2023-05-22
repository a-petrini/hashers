#pragma once

#include "openssl_hashers.hpp"

#include "benchmark/benchmark.h"

void openssl_sha1_perf(benchmark::State& state);
void openssl_sha256_perf(benchmark::State& state);
void openssl_sha512_perf(benchmark::State& state);