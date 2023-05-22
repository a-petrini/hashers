#pragma once

#include <vector>

#include "openssl/evp.h"

std::vector<unsigned char> openssl_sha1_hasher(EVP_MD_CTX * const mdctx, const std::vector<char> & filebuffer);
std::vector<unsigned char> openssl_sha256_hasher(EVP_MD_CTX * const mdctx, const std::vector<char> & filebuffer);
std::vector<unsigned char> openssl_sha512_hasher(EVP_MD_CTX * const mdctx, const std::vector<char> & filebuffer);