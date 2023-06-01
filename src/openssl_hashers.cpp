#include "openssl_hashers.hpp"

std::vector<unsigned char> openssl_digest(const EVP_MD *md, EVP_MD_CTX *mdctx, const char *data, const size_t count)
{
    const size_t kDigestLength{static_cast<size_t>(EVP_MD_size(md))};
    std::vector<unsigned char> output(kDigestLength);
    EVP_DigestInit_ex(mdctx, md, nullptr); // Already implies a reset
    EVP_DigestUpdate(mdctx, data, count);
    EVP_DigestFinal_ex(mdctx, output.data(), nullptr);
    return output;
}
