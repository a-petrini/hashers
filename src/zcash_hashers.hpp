#pragma once

#include <vector>

std::vector<unsigned char> zcash_sha1_hasher(const std::vector<char> & filebuffer);
std::vector<unsigned char> zcash_sha256_hasher(const std::vector<char> & filebuffer);
std::vector<unsigned char> zcash_sha512_hasher(const std::vector<char> & filebuffer);