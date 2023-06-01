#include "zcash_hashers.hpp"


std::vector<unsigned char> zcash_sha1_hasher(const char *data, size_t len)
{
    static auto hasher{zcash::CSHA1()};
    std::vector<unsigned char> output(zcash::CSHA1::OUTPUT_SIZE); // 20
    hasher.Reset().Write(reinterpret_cast<const unsigned char *>(data), len).Finalize(output.data());
    return output;
}

std::vector<unsigned char> zcash_sha256_hasher(const char *data, size_t len)
{
    static auto hasher{zcash::CSHA256()};
    std::vector<unsigned char> output(zcash::CSHA256::OUTPUT_SIZE); // 32
    hasher.Reset().Write(reinterpret_cast<const unsigned char *>(data), len).Finalize(output.data());
    return output;
}

std::vector<unsigned char> zcash_sha512_hasher(const char *data, size_t len)
{
    static auto hasher{zcash::CSHA512()};
    std::vector<unsigned char> output(zcash::CSHA512::OUTPUT_SIZE); // 64
    hasher.Reset().Write(reinterpret_cast<const unsigned char *>(data), len).Finalize(output.data());
    return output;
}
