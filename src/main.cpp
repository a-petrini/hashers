#include <iostream>
#include <string>
#include <unistd.h>
#include <functional>

#include "common.h"
#include "configuration.h"
#include "utilbellebelle.hpp"

#include "benchmark/benchmark.h"

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

class Finally
{
public:
    Finally(std::function<void()> f) : f_(std::move(f)) {}
    ~Finally() { f_(); }

private:
    std::function<void()> f_;
};

int main(int argc, char **argv)
{

    // Allow parsing of command line arguments for benchmark
    ::benchmark::Initialize(&argc, argv);
    Finally cleanup([]() { ::benchmark::Shutdown(); });

    // Detect if a test file has been specified by redirecting input
    // Note !! Works only on POSIX systems
    if (!isatty(fileno(stdin)))
    {
        auto it{std::istreambuf_iterator<char>(std::cin)};
        filebuffer.assign(it, {});
        if(filebuffer.size() < 64)
        {
            std::cout << TXT_BIRED "Error: " TXT_BIBLU "Input too small (min 64)" TXT_NORML << std::endl;
            return 1;
        }
    }
    else
    {
        const std::string sample_data{"The quick brown fox jumps over the lazy dog\n"};
        filebuffer.insert(filebuffer.end(), sample_data.begin(), sample_data.end());
        std::cout << TXT_BIYLW "No input specified, just running correctness test with dummy string" TXT_NORML << std::endl;
    }

    std::cout << TXT_BIBLU "Supporting AVX instruction set? " TXT_BIBLK << std::boolalpha << zcash::AVXEnabled() << TXT_NORML "\n"
              << TXT_BIBLU "Zcash SHA-256 autodetected implementation: " TXT_BIBLK << zcash::SHA256AutoDetect() << TXT_NORML << std::endl;

    // // Override autoselection of ZCash SHA-256 implementation
    // zcash::SHA256_selectDefault();   std::cout << TXT_BIBLU << "Zcash SHA-256 overridden implementation: " << TXT_BIBLK << "default" << std::endl;
    // zcash::SHA256_selectShani();     std::cout << TXT_BIBLU << "Zcash SHA-256 overridden implementation: " << TXT_BIBLK << "SHAni" << std::endl;
    // zcash::SHA256_selectSSE4();      std::cout << TXT_BIBLU << "Zcash SHA-256 overridden implementation: " << TXT_BIBLK << "SSE4" << std::endl;
    // zcash::SHA256_selectSSE41();     std::cout << TXT_BIBLU << "Zcash SHA-256 overridden implementation: " << TXT_BIBLK << "SSE4.1" << std::endl;
    // zcash::SHA256_selectAVX();       std::cout << TXT_BIBLU << "Zcash SHA-256 overridden implementation: " << TXT_BIBLK << "AVX2" << std::endl;

    //// zen SHA-1 hasher
    std::vector<unsigned char> zenSha1Output = zen_sha1_hasher(filebuffer.data(), filebuffer.size());
    std::cout << TXT_BICYA << "zen SHA-1:       " << TXT_NORML;
    printShaOut(zenSha1Output);
    //// zen SHA-256 hasher
    std::vector<unsigned char> zenSha256Output = zen_sha256_hasher(filebuffer.data(), filebuffer.size());
    std::cout << TXT_BICYA << "zen SHA-256:     " << TXT_NORML;
    printShaOut(zenSha256Output);
    //// zen SHA-512 hasher
    std::vector<unsigned char> zenSha512Output = zen_sha512_hasher(filebuffer.data(), filebuffer.size());
    std::cout << TXT_BICYA << "zen SHA-512:     " << TXT_NORML;
    printShaOut(zenSha512Output);

    //////////////////

    //// zcash SHA-1 hasher
    std::vector<unsigned char> zcashSha1Output = zcash_sha1_hasher(filebuffer.data(), filebuffer.size());
    std::cout << TXT_BICYA << "zcash SHA-1:     " << TXT_NORML;
    printShaOut(zcashSha1Output);
    //// zcash SHA-256 hasher
    std::vector<unsigned char> zcashSha256Output = zcash_sha256_hasher(filebuffer.data(), filebuffer.size());
    std::cout << TXT_BICYA << "zcash SHA-256:   " << TXT_NORML;
    printShaOut(zcashSha256Output);
    //// zcash SHA-512 hasher
    std::vector<unsigned char> zcashSha512Output = zcash_sha512_hasher(filebuffer.data(), filebuffer.size());
    std::cout << TXT_BICYA << "zcash SHA-512:   " << TXT_NORML;
    printShaOut(zcashSha512Output);

    //////////////////

    //// OpenSSL SHA-1 hasher
    std::vector<unsigned char> openSSLSha1Output = openssl_sha1_hasher(filebuffer.data(), filebuffer.size());
    std::cout << TXT_BICYA << "OpenSSL SHA-1:   " << TXT_NORML;
    printShaOut(openSSLSha1Output);
    //// OpenSSL SHA-256 hasher
    std::vector<unsigned char> openSSLSha256Output = openssl_sha256_hasher(filebuffer.data(), filebuffer.size());
    std::cout << TXT_BICYA << "OpenSSL SHA-256: " << TXT_NORML;
    printShaOut(openSSLSha256Output);
    //// OpenSSL SHA-512 hasher
    std::vector<unsigned char> openSSLSha512Output = openssl_sha512_hasher(filebuffer.data(), filebuffer.size());
    std::cout << TXT_BICYA << "OpenSSL SHA-512: " << TXT_NORML;
    printShaOut(openSSLSha512Output);

    if (filebuffer.size() >= 64)
    {
        std::cout << "\n" TXT_BIGRN << "Running performance test on input" << TXT_NORML << std::endl;

        BENCHMARK(zen_sha1_perf)->RangeMultiplier(2)->Range(64, filebuffer.size());
        BENCHMARK(zen_sha256_perf)->RangeMultiplier(2)->Range(64, filebuffer.size());
        BENCHMARK(zen_sha512_perf)->RangeMultiplier(2)->Range(64, filebuffer.size());

        BENCHMARK(zcash_sha1_perf)->RangeMultiplier(2)->Range(64, filebuffer.size());
        BENCHMARK(zcash_sha256_perf)->RangeMultiplier(2)->Range(64, filebuffer.size());
        BENCHMARK(zcash_sha512_perf)->RangeMultiplier(2)->Range(64, filebuffer.size());

        BENCHMARK(openssl_sha1_perf)->RangeMultiplier(2)->Range(64, filebuffer.size());
        BENCHMARK(openssl_sha256_perf)->RangeMultiplier(2)->Range(64, filebuffer.size());
        BENCHMARK(openssl_sha512_perf)->RangeMultiplier(2)->Range(64, filebuffer.size());

        ::benchmark::RunSpecifiedBenchmarks();
    }

    return 0;
}
