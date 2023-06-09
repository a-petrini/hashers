# hashers
A small framework for comparing famous hasher implementations

## Prerequisites
This software requires:
```
a c++ compiler supporting c++17
cmake >=3.14
```

Google Benchmark and OpenSSL libraries are automatically dowloaded and compiled at compile time


## Compiling
From the root of the project:
```
mkdir bin && cd bin
cmake -DOPENSSL_BUILD_VERSION=3.1.0 -DBUILD_OPENSSL=ON -DCMAKE_BUILD_TYPE=RelWithDebInfo ../src
make -j 4
```

## What does it do?
This project tests the correctness and evaluates the running performance of several implementations for some of the hashing algorithms currently used in Zend.

At the moment, the following algorithms are evaluated:
```
SHA-1
SHA-256
SHA-512
```

Implementations are extracted or are privided by the following packages / libraries:

* [zen](https://github.com/HorizenOfficial/zen): copied from the official repository
* [zcash](https://github.com/zcash/zcash): copied from the official repository
* [OpenSSL](https://github.com/openssl/openssl): downloaded and compiled at compile time


## Running the program
When launched with no command line arguments, the program hashes the following string (hardcoded):
```
The quick brown fox jumps over the lazy dog
<new line>
```
using all the algorithms listed in the previous paragraph.

Note that `assets/test.txt` contains the same sentence, so that it is possible to compare the results i.e. by using Linux utilities:
```
sha1sum assets/test.txt
sha256sum assets/test.txt
sha512sum assets/test.txt
```

The program accepts an input file as command line argument.

When so, it hashes the input file using all the algorithms listed in the previous paragraph.
It also benchmarks the algorithms on substrings of the input file of different lengths (from 64 Bytes to 4MB, power of 2 step), leveraging Google Benchmark library for measuring execution times and providing additional statistics.

Note that a 4 MBytes or larger file is **required**. Smaller file will result in undefined behaviour.

----

## List of available implementations

* zen
```
SHA-1: C
SHA-256: C
SHA-512: C
```

* zcash
```
SHA-1: C
SHA-256: C; C + SSE4 intr.; C + SSE4.1 intr.; C + AVX2 intr.; C + Intel SHA intr. 
SHA-512: C
```

* OpenSSL
```
SHA-1: automatically selects one of the digest implementation (opefully, the most optimized)
SHA-256: automatically selects one of the digest implementation (opefully, the most optimized)
SHA-512: automatically selects one of the digest implementation (opefully, the most optimized)
```