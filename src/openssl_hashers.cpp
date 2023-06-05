#include "openssl_hashers.hpp"

std::vector<unsigned char> openssl_sha1_hasher(const char *data, size_t len)
{
    static openssl::CSHA1 hasher{};
    std::vector<unsigned char> output(20);
    hasher.Reset().Write(reinterpret_cast<const unsigned char *>(data), len).Finalize(output.data());
    return output;
}

std::vector<unsigned char> openssl_sha256_hasher(const char *data, size_t len)
{
    static openssl::CSHA256 hasher{};
    std::vector<unsigned char> output(32);
    hasher.Reset().Write(reinterpret_cast<const unsigned char *>(data), len).Finalize(output.data());
    return output;
}

std::vector<unsigned char> openssl_sha512_hasher(const char *data, size_t len)
{
    static openssl::CSHA512 hasher{};
    std::vector<unsigned char> output(64);
    hasher.Reset().Write(reinterpret_cast<const unsigned char *>(data), len).Finalize(output.data());
    return output;
}
