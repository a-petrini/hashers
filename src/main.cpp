#include <iostream>
#include <vector>
#include <string>

#include "common.h"
#include "configuration.h"
#include "utilbellebelle.hpp"

#include "benchmark/benchmark.h"

#include "zcash/sha256.h"

#include "zen_hashers.hpp"
#include "zcash_hashers.hpp"
#include "openssl_hashers.hpp"

#include "zen_hashers_tests.hpp"
#include "zcash_hashers_tests.hpp"
#include "openssl_hashers_tests.hpp"

////// Reference results
// const char * exampleData {"The quick brown fox jumps over the lazy dog\n"}; // length = 44
// Evaluated on https://emn178.github.io/online-tools/sha1.html
// --------
// sha1:   be417768b5c3c5c1d9bcb2e7c119196dd76b5570
// sha256: c03905fcdab297513a620ec81ed46ca44ddb62d41cbbd83eb4a5a3592be26a69
// sha512: a12ac6bdd854ac30c5cc5b576e1ee2c060c0d8c2bec8797423d7119aa2b962f7f30ce2e39879cbff0109c8f0a3fd9389a369daae45df7d7b286d7d98272dc5b1
// 
// assets/test.txt
// --------
// sha1sum:   be417768b5c3c5c1d9bcb2e7c119196dd76b5570  test.txt
// sha256sum: c03905fcdab297513a620ec81ed46ca44ddb62d41cbbd83eb4a5a3592be26a69  test.txt
// sha512sum: a12ac6bdd854ac30c5cc5b576e1ee2c060c0d8c2bec8797423d7119aa2b962f7f30ce2e39879cbff0109c8f0a3fd9389a369daae45df7d7b286d7d98272dc5b1  test.txt
//
// assets/100M.txt
// --------
// sha1sum:   cd8c10d7a27e7b73d37680e54357e5d54e8d330d  100M.txt
// sha256sum: 5ebc45fd76da5fefc13a21d5ce3a86fdab7653d0c0e3ce98a65be108f3896d1d  100M.txt
// sha512sum: 7c201e142d973538d6fa7be43d5f00a9684c35d4117d98ba191b785ab77da0574451019878bd21b28aab1a402e04726d69e9f5bd335fa7a3f80877693629de6c  100M.txt
//
// assets/4M.txt
// --------
// sha1sum:   d851111465cb4829cb96d12b5b13194430e75d02  4M.txt
// sha256sum: 428b2e5b1496cf2d56bcc94648c6398600e44f8a5105a86af93e577df88e146a  4M.txt
// sha512sum: ae7b4027f4a74fe07874b12ae2fc47e92a83c81f50b68f18793a401def835695a4077094ab38c13bb42586f425cffbbbc8bc85d1abeaa467785f3ef97b03ac95  4M.txt

//////

// Naaaaa, mannaggia! Globali!
std::vector<char> filebuffer;
EVP_MD_CTX* mdctx = nullptr;

int main(int argc, char ** argv) {

    bool doPerfTests = false;

    if (argc > 1) {
        filebuffer = readBuffer(argv[1]);
        doPerfTests = true;
        std::cout << TXT_BIGRN << "Running correctness test on input file" << TXT_NORML << std::endl;
    }
    else {
        // Added a \n to be compliant with the content of test.txt
        const char * exampleData {"The quick brown fox jumps over the lazy dog\n"};
        std::copy(exampleData, exampleData + 44, std::back_inserter(filebuffer));
        std::cout << TXT_BIYLW << "No input file specified, just running correctness test with dummy string" << TXT_NORML << std::endl;
    }

    std::cout << TXT_BIBLU << "Supporting AVX instruction set? " << TXT_BIBLK << std::boolalpha << zcash::AVXEnabled() << TXT_NORML << std::endl;
    std::cout << TXT_BIBLU << "Zcash SHA-256 autodetected implementation: " << TXT_BIBLK << zcash::SHA256AutoDetect() << TXT_NORML << std::endl;

    // // Override autoselection of ZCash SHA-256 implementation
    // zcash::SHA256_selectDefault();   std::cout << TXT_BIBLU << "Zcash SHA-256 overridden implementation: " << TXT_BIBLK << "default" << std::endl;
    // zcash::SHA256_selectShani();     std::cout << TXT_BIBLU << "Zcash SHA-256 overridden implementation: " << TXT_BIBLK << "SHAni" << std::endl;
    // zcash::SHA256_selectSSE4();      std::cout << TXT_BIBLU << "Zcash SHA-256 overridden implementation: " << TXT_BIBLK << "SSE4" << std::endl;
    // zcash::SHA256_selectSSE41();     std::cout << TXT_BIBLU << "Zcash SHA-256 overridden implementation: " << TXT_BIBLK << "SSE4.1" << std::endl;
    // zcash::SHA256_selectAVX();       std::cout << TXT_BIBLU << "Zcash SHA-256 overridden implementation: " << TXT_BIBLK << "AVX2" << std::endl;

    //// zen SHA-1 hasher
    std::vector<unsigned char> zenSha1Output   = zen_sha1_hasher(filebuffer);
    std::cout << TXT_BICYA << "zen SHA-1:       " << TXT_NORML;
    printShaOut(zenSha1Output);
    //// zen SHA-256 hasher
    std::vector<unsigned char> zenSha256Output = zen_sha256_hasher(filebuffer);
    std::cout << TXT_BICYA << "zen SHA-256:     " << TXT_NORML;
    printShaOut(zenSha256Output);
    //// zen SHA-512 hasher
    std::vector<unsigned char> zenSha512Output = zen_sha512_hasher(filebuffer);
    std::cout << TXT_BICYA << "zen SHA-512:     " << TXT_NORML;
    printShaOut(zenSha512Output);

    //////////////////

    //// zcash SHA-1 hasher
    std::vector<unsigned char> zcashSha1Output   = zcash_sha1_hasher(filebuffer);
    std::cout << TXT_BICYA << "zcash SHA-1:     " << TXT_NORML;
    printShaOut(zcashSha1Output);
    //// zcash SHA-256 hasher
    std::vector<unsigned char> zcashSha256Output = zcash_sha256_hasher(filebuffer);
    std::cout << TXT_BICYA << "zcash SHA-256:   " << TXT_NORML;
    printShaOut(zcashSha256Output);
    //// zcash SHA-512 hasher
    std::vector<unsigned char> zcashSha512Output = zcash_sha512_hasher(filebuffer);
    std::cout << TXT_BICYA << "zcash SHA-512:   " << TXT_NORML;
    printShaOut(zcashSha512Output);

    //////////////////

    mdctx = EVP_MD_CTX_new();

    //// OpenSSL SHA-1 hasher
    std::vector<unsigned char> openSSLSha1Output = openssl_sha1_hasher(mdctx, filebuffer);
    std::cout << TXT_BICYA << "OpenSSL SHA-1:   " << TXT_NORML;
    printShaOut(openSSLSha1Output);
    //// OpenSSL SHA-256 hasher
    std::vector<unsigned char> openSSLSha256Output = openssl_sha256_hasher(mdctx, filebuffer);
    std::cout << TXT_BICYA << "OpenSSL SHA-256: " << TXT_NORML;
    printShaOut(openSSLSha256Output);
    //// OpenSSL SHA-512 hasher
    std::vector<unsigned char> openSSLSha512Output = openssl_sha512_hasher(mdctx, filebuffer);
    std::cout << TXT_BICYA << "OpenSSL SHA-512: " << TXT_NORML;
    printShaOut(openSSLSha512Output);

    if (doPerfTests) {
        std::cout << std::endl << TXT_BIGRN << "Running performance test on input file" << TXT_NORML << std::endl;

        BENCHMARK(zen_sha1_perf)->RangeMultiplier(2)->Range(64, 64<<16);
        BENCHMARK(zen_sha256_perf)->RangeMultiplier(2)->Range(64, 64<<16);
        BENCHMARK(zen_sha512_perf)->RangeMultiplier(2)->Range(64, 64<<16);

        BENCHMARK(zcash_sha1_perf)->RangeMultiplier(2)->Range(64, 64<<16);
        BENCHMARK(zcash_sha256_perf)->RangeMultiplier(2)->Range(64, 64<<16);
        BENCHMARK(zcash_sha512_perf)->RangeMultiplier(2)->Range(64, 64<<16);

        BENCHMARK(openssl_sha1_perf)->RangeMultiplier(2)->Range(64, 64<<16);
        BENCHMARK(openssl_sha256_perf)->RangeMultiplier(2)->Range(64, 64<<16);
        BENCHMARK(openssl_sha512_perf)->RangeMultiplier(2)->Range(64, 64<<16);

        ::benchmark::Initialize(&argc, argv);
        ::benchmark::RunSpecifiedBenchmarks();
        ::benchmark::Shutdown();
    }

    EVP_MD_CTX_free(mdctx);

    return 0;
}