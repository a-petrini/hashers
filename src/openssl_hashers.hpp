#pragma once

#include <vector>

#include "openssl/evp.h"

std::vector<unsigned char> openssl_sha1_hasher(const EVP_MD* md, EVP_MD_CTX* mdctx, const std::vector<char> &filebuffer);
std::vector<unsigned char> openssl_sha256_hasher(const EVP_MD* md, EVP_MD_CTX* mdctx, const std::vector<char> &filebuffer);
std::vector<unsigned char> openssl_sha512_hasher(const EVP_MD* md, EVP_MD_CTX* mdctx, const std::vector<char> &filebuffer);