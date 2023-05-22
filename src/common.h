#pragma once

#include <vector>
#include "openssl/evp.h"

extern std::vector<char> filebuffer;
extern EVP_MD_CTX* mdctx;