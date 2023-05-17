# hashing algorithms tests
# 2023 - Alessandro Petrini - Horizen Labs

### For CMake examples and tutorials:
# https://github.com/Mizux/cmake-cpp/tree/main
# https://gitlab.com/CLIUtils/modern-cmake/-/tree/master/examples/extended-project
###

# -DCMAKE_BUILD_TYPE=Release|Debug|RelWithDebInfo|MinSizeRel

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

# FetchContent added in CMake 3.11, downloads during the configure step
# FetchContent_MakeAvailable was added in CMake 3.14; simpler usage
include(FetchContent)

### submodule examples:
## Accumulator library
## This is header only, so could be replaced with git submodules or FetchContent
## Adds Boost::boost
# find_package(Boost REQUIRED)

## Formatting library
## Adds fmt::fmt
# FetchContent_Declare(
#   fmtlib
#   GIT_REPOSITORY https://github.com/fmtlib/fmt.git
#   GIT_TAG 5.3.0)
# FetchContent_MakeAvailable(fmtlib)

###################

add_executable(onetest)

target_include_directories(onetest PRIVATE
	"${PROJECT_BINARY_DIR}"
)

configure_file(configuration.h.in configuration.h)
target_sources(onetest PRIVATE
	main.cpp
)

# target_link_libraries(onetest PRIVATE
# )


