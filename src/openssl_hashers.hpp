#pragma once

#include <vector>

#include "openssl/evp.h"

std::vector<unsigned char> openssl_digest(const EVP_MD* md, EVP_MD_CTX* mdctx, const char* data, const size_t count);
