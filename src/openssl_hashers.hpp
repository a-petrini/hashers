#pragma once

#include <vector>

#include "openssl/digest.hpp"

std::vector<unsigned char> openssl_sha1_hasher(const char *data, std::size_t len);
std::vector<unsigned char> openssl_sha256_hasher(const char *data, std::size_t len);
std::vector<unsigned char> openssl_sha512_hasher(const char *data, std::size_t len);
