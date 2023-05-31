#pragma once

#include <vector>

std::vector<unsigned char> zen_sha1_hasher(const char *data, std::size_t len);
std::vector<unsigned char> zen_sha256_hasher(const char *data, std::size_t len);
std::vector<unsigned char> zen_sha512_hasher(const char *data, std::size_t len);
