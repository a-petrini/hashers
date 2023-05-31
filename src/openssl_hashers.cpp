#include "openssl_hashers.hpp"

#include <iostream>
#include <vector>

#include "configuration.h"
#include "utilbellebelle.hpp"

#include "openssl/sha.h"
#include "openssl/evp.h"
#include "openssl/err.h"

std::vector<unsigned char> openssl_sha1_hasher(const EVP_MD *md, EVP_MD_CTX *mdctx, const std::vector<char> &filebuffer)
{
    std::vector<unsigned char> output(20);
    EVP_DigestInit_ex(mdctx, md, nullptr); // Already implies a reset
    EVP_DigestUpdate(mdctx, filebuffer.data(), filebuffer.size());
    EVP_DigestFinal_ex(mdctx, output.data(), nullptr);
    return output;
}

std::vector<unsigned char> openssl_sha256_hasher(const EVP_MD *md, EVP_MD_CTX *mdctx, const std::vector<char> &filebuffer)
{

    std::vector<unsigned char> output(32);
    EVP_DigestInit_ex(mdctx, md, nullptr); // Already implies a reset
    EVP_DigestUpdate(mdctx, filebuffer.data(), filebuffer.size());
    EVP_DigestFinal_ex(mdctx, output.data(), nullptr);
    return output;
}

std::vector<unsigned char> openssl_sha512_hasher(const EVP_MD *md, EVP_MD_CTX *mdctx, const std::vector<char> &filebuffer)
{
    std::vector<unsigned char> output(64);
    EVP_DigestInit_ex(mdctx, md, nullptr); // Already implies a reset
    EVP_DigestUpdate(mdctx, filebuffer.data(), filebuffer.size());
    EVP_DigestFinal_ex(mdctx, output.data(), nullptr);
    return output;
}
