#include "zcash_hashers.hpp"

#include <iostream>
#include <vector>

#include "configuration.h"
#include "utilbellebelle.hpp"

#include "zcash/sha1.h"
#include "zcash/sha256.h"
#include "zcash/sha512.h"

std::vector<unsigned char> zcash_sha1_hasher(const std::vector<char> & filebuffer) {
    std::vector<unsigned char> zcashSha1Output(zcash::CSHA1::OUTPUT_SIZE); // 20
    zcash::CSHA1().Write(reinterpret_cast<const unsigned char*>(filebuffer.data()), filebuffer.size()).Finalize(zcashSha1Output.data());
    return zcashSha1Output;
}

std::vector<unsigned char> zcash_sha256_hasher(const std::vector<char> & filebuffer) {
    std::vector<unsigned char> zcashSha256Output(zcash::CSHA256::OUTPUT_SIZE); // 32
    zcash::CSHA256().Write(reinterpret_cast<const unsigned char*>(filebuffer.data()), filebuffer.size()).Finalize(zcashSha256Output.data());
    return zcashSha256Output;
}

std::vector<unsigned char> zcash_sha512_hasher(const std::vector<char> & filebuffer) {
    std::vector<unsigned char> zcashSha512Output(zcash::CSHA512::OUTPUT_SIZE); // 64
    zcash::CSHA512().Write(reinterpret_cast<const unsigned char*>(filebuffer.data()), filebuffer.size()).Finalize(zcashSha512Output.data());
    return zcashSha512Output;
}
