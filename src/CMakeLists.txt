# hashing algorithms tests
# 2023 - Alessandro Petrini - Horizen Labs

### For CMake examples and tutorials:
# https://github.com/Mizux/cmake-cpp/tree/main
# https://gitlab.com/CLIUtils/modern-cmake/-/tree/master/examples/extended-project
###

###
# -DCMAKE_BUILD_TYPE=Release|Debug|RelWithDebInfo|MinSizeRel
###

###
# OpenSSL build (from https://github.com/viaduck/openssl-cmake)
# 1. Add OpenSSL-CMake as a submodule to your Git project using git submodule add <URL> src/extern/openssl-cmake   <<-- in hashing/src
# 2. Initialize the submodule using git submodule update --init
# 3. In your CMakeLists.txt include the directory using add_subdirectory(src/extern/openssl-cmake)
# 4. Link against ssl and crypto targets, which will also include the headers
#
# cmake -DOPENSSL_BUILD_VERSION=3.1.0 -DBUILD_OPENSSL=ON ../src/
###

cmake_minimum_required(VERSION 3.16)

project(
  HashingFunctions
  VERSION 0.1
  DESCRIPTION "Testing alternative implementations of hashing functions"
  LANGUAGES CXX
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(BENCHMARK_ENABLE_TESTING OFF)   # Disable Google Test for Google Benchmark

add_subdirectory("extern/openssl-cmake")
add_subdirectory("extern/google-benchmark")

###################

configure_file(configuration.h.in configuration.h)

add_executable(hashers)

target_include_directories(hashers PRIVATE
	"${PROJECT_BINARY_DIR}"
  zen
  zcash
  .
)

set_source_files_properties(zcash/sha256_avx2.cpp PROPERTIES COMPILE_OPTIONS -mavx2)
set_source_files_properties(zcash/sha256_shani.cpp PROPERTIES COMPILE_OPTIONS "-msha;-msse4.1")
set_source_files_properties(zcash/sha256_sse4.cpp PROPERTIES COMPILE_OPTIONS -msse4)
set_source_files_properties(zcash/sha256_sse41.cpp PROPERTIES COMPILE_OPTIONS -msse4)

set(COMMON_SRC
  openssl_hashers.cpp
  zen_hashers.cpp
  zcash_hashers.cpp
  zen/sha1.cpp
  zen/sha256.cpp
  zen/sha512.cpp
  zcash/sha1.cpp
  zcash/sha256.cpp
  zcash/sha256_avx2.cpp
  zcash/sha256_shani.cpp
  zcash/sha256_sse41.cpp
  zcash/sha256_sse4.cpp
  zcash/sha512.cpp
)

set(PERFTEST_SRC
  zen_hashers_tests.cpp
  zcash_hashers_tests.cpp
  openssl_hashers_tests.cpp
)

target_sources(hashers PRIVATE
  main.cpp
  ${COMMON_SRC}
  ${PERFTEST_SRC}
)

target_link_libraries(hashers PRIVATE
ssl
crypto
benchmark
)


