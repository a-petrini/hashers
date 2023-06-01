#include "zen_hashers.hpp"

#include "zen/sha1.h"
#include "zen/sha256.h"
#include "zen/sha512.h"

std::vector<unsigned char> zen_sha1_hasher(const char *data, std::size_t len)
{
    static auto hasher{zen::CSHA1()};
    std::vector<unsigned char> output(zen::CSHA1::OUTPUT_SIZE); // 20
    hasher.Reset().Write(reinterpret_cast<const unsigned char *>(data), len).Finalize(output.data());
    return output;
}

std::vector<unsigned char> zen_sha256_hasher(const char *data, std::size_t len)
{
    static auto hasher{zen::CSHA256()};
    std::vector<unsigned char> output(zen::CSHA256::OUTPUT_SIZE); // 32
    hasher.Reset().Write(reinterpret_cast<const unsigned char *>(data), len).Finalize(output.data());
    return output;
}

std::vector<unsigned char> zen_sha512_hasher(const char *data, std::size_t len)
{
    static auto hasher{zen::CSHA512()};
    std::vector<unsigned char> output(zen::CSHA512::OUTPUT_SIZE); // 64
    zen::CSHA512().Write(reinterpret_cast<const unsigned char *>(data), len).Finalize(output.data());
    return output;
}