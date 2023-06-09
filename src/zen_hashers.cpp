#include "zen_hashers.hpp"

#include <iostream>
#include <vector>

#include "configuration.h"
#include "utilbellebelle.hpp"

#include "zen/sha1.h"
#include "zen/sha256.h"
#include "zen/sha512.h"

std::vector<unsigned char> zen_sha1_hasher(const std::vector<char> & filebuffer) {
    std::vector<unsigned char> zenSha1Output(zen::CSHA1::OUTPUT_SIZE); // 20
    zen::CSHA1().Write(reinterpret_cast<const unsigned char*>(filebuffer.data()), filebuffer.size()).Finalize(zenSha1Output.data());
    return zenSha1Output;
}

std::vector<unsigned char> zen_sha256_hasher(const std::vector<char> & filebuffer) {
    std::vector<unsigned char> zenSha256Output(zen::CSHA256::OUTPUT_SIZE); // 32
    zen::CSHA256().Write(reinterpret_cast<const unsigned char*>(filebuffer.data()), filebuffer.size()).Finalize(zenSha256Output.data());
    return zenSha256Output;
}

std::vector<unsigned char> zen_sha512_hasher(const std::vector<char> & filebuffer) {
    std::vector<unsigned char> zenSha512Output(zen::CSHA512::OUTPUT_SIZE); // 64
    zen::CSHA512().Write(reinterpret_cast<const unsigned char*>(filebuffer.data()), filebuffer.size()).Finalize(zenSha512Output.data());
    return zenSha512Output;
}