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
cmake -DOPENSSL_BUILD_VERSION=3.1.0 -DBUILD_OPENSSL=ON ../src
make -j 4
```