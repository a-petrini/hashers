#pragma once

#include <vector>

#include "zcash/sha1.h"
#include "zcash/sha256.h"
#include "zcash/sha512.h"

std::vector<unsigned char> zcash_sha1_hasher(const char* data, std::size_t len);
std::vector<unsigned char> zcash_sha256_hasher(const char *data, std::size_t len);
std::vector<unsigned char> zcash_sha512_hasher(const char *data, std::size_t len);