#include "openssl_hashers.hpp"

#include <iostream>
#include <vector>

#include "configuration.h"
#include "utilbellebelle.hpp"

#include "openssl/sha.h"
#include "openssl/evp.h"
#include "openssl/err.h"


std::vector<unsigned char> openssl_sha1_hasher(EVP_MD_CTX * const mdctx, const std::vector<char> & filebuffer) {
    EVP_MD *openssl_sha1_md = nullptr;
    unsigned int mdLength = 0;
    std::vector<unsigned char> openSSLSha1Output(EVP_MAX_MD_SIZE);    // 64

    EVP_MD_CTX_reset(mdctx);
    openssl_sha1_md   = EVP_MD_fetch(NULL, "SHA-1",   NULL);
    EVP_DigestInit_ex2(mdctx, openssl_sha1_md,   NULL);
    EVP_DigestUpdate(mdctx, filebuffer.data(), filebuffer.size());
    EVP_DigestFinal_ex(mdctx, openSSLSha1Output.data(), &mdLength);
    openSSLSha1Output.resize(mdLength);
    EVP_MD_free(openssl_sha1_md);
    return openSSLSha1Output;
}

std::vector<unsigned char> openssl_sha256_hasher(EVP_MD_CTX * const mdctx, const std::vector<char> & filebuffer) {
    EVP_MD *openssl_sha256_md = nullptr;
    unsigned int mdLength = 0;
    std::vector<unsigned char> openSSLSha256Output(EVP_MAX_MD_SIZE);  // 64

    EVP_MD_CTX_reset(mdctx);
    openssl_sha256_md = EVP_MD_fetch(NULL, "SHA-256", NULL);
    EVP_DigestInit_ex2(mdctx, openssl_sha256_md, NULL);
    EVP_DigestUpdate(mdctx, filebuffer.data(), filebuffer.size());
    EVP_DigestFinal_ex(mdctx, openSSLSha256Output.data(), &mdLength);
    openSSLSha256Output.resize(mdLength);
    EVP_MD_free(openssl_sha256_md);
    return openSSLSha256Output;

}

std::vector<unsigned char> openssl_sha512_hasher(EVP_MD_CTX * const mdctx, const std::vector<char> & filebuffer) {
    EVP_MD *openssl_sha512_md = nullptr;
    unsigned int mdLength = 0;
    std::vector<unsigned char> openSSLSha512Output(EVP_MAX_MD_SIZE);  // 64

    EVP_MD_CTX_reset(mdctx);
    openssl_sha512_md = EVP_MD_fetch(NULL, "SHA-512", NULL);
    EVP_DigestInit_ex2(mdctx, openssl_sha512_md, NULL);
    EVP_DigestUpdate(mdctx, filebuffer.data(), filebuffer.size());
    EVP_DigestFinal_ex(mdctx, openSSLSha512Output.data(), &mdLength);
    openSSLSha512Output.resize(mdLength);
    EVP_MD_free(openssl_sha512_md);
    return openSSLSha512Output;

}
