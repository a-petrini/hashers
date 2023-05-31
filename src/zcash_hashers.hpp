#pragma once

#include <vector>

std::vector<unsigned char> zcash_sha1_hasher(const char* data, std::size_t len);
std::vector<unsigned char> zcash_sha256_hasher(const char *data, std::size_t len);
std::vector<unsigned char> zcash_sha512_hasher(const char *data, std::size_t len);