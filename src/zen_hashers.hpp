#pragma once

#include <vector>

std::vector<unsigned char> zen_sha1_hasher(const std::vector<char> & filebuffer);
std::vector<unsigned char> zen_sha256_hasher(const std::vector<char> & filebuffer);
std::vector<unsigned char> zen_sha512_hasher(const std::vector<char> & filebuffer);

