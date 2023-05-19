#include <iostream>
#include <vector>
#include <string>

#include "configuration.h"
#include "utilbellebelle.hpp"

#include "zen/sha1.h"
#include "zen/sha256.h"
#include "zen/sha512.h"

#include "zcash/sha1.h"
#include "zcash/sha256.h"
#include "zcash/sha512.h"

#include "openssl/sha.h"
#include "openssl/evp.h"
#include "openssl/err.h"


////// Reference results
// const char * exampleData {"The quick brown fox jumps over the lazy dog\n"}; // length = 44
// Evaluated on https://emn178.github.io/online-tools/sha1.html
// --------
// sha1:   be417768b5c3c5c1d9bcb2e7c119196dd76b5570
// sha256: c03905fcdab297513a620ec81ed46ca44ddb62d41cbbd83eb4a5a3592be26a69
// sha512: a12ac6bdd854ac30c5cc5b576e1ee2c060c0d8c2bec8797423d7119aa2b962f7f30ce2e39879cbff0109c8f0a3fd9389a369daae45df7d7b286d7d98272dc5b1
// 
// test.txt
// --------
// sha1sum:   be417768b5c3c5c1d9bcb2e7c119196dd76b5570  test.txt
// sha256sum: c03905fcdab297513a620ec81ed46ca44ddb62d41cbbd83eb4a5a3592be26a69  test.txt
// sha512sum: a12ac6bdd854ac30c5cc5b576e1ee2c060c0d8c2bec8797423d7119aa2b962f7f30ce2e39879cbff0109c8f0a3fd9389a369daae45df7d7b286d7d98272dc5b1  test.txt
//
// 100M.txt
// --------
// sha1sum:   cd8c10d7a27e7b73d37680e54357e5d54e8d330d  100M.txt
// sha256sum: 5ebc45fd76da5fefc13a21d5ce3a86fdab7653d0c0e3ce98a65be108f3896d1d  100M.txt
// sha512sum: 7c201e142d973538d6fa7be43d5f00a9684c35d4117d98ba191b785ab77da0574451019878bd21b28aab1a402e04726d69e9f5bd335fa7a3f80877693629de6c  100M.txt
//////

int main(int argc, char ** argv) {

    std::vector<char> filebuffer;
    if (argc > 1)
        filebuffer = readBuffer(argv[1]);
    else {
        // Added a \n to be compliant with the content of test.txt
        const char * exampleData {"The quick brown fox jumps over the lazy dog\n"};
        std::copy(exampleData, exampleData + 44, std::back_inserter(filebuffer));
    }

    //// zen SHA-1 hasher
    std::vector<unsigned char> zenSha1Output(zen::CSHA1::OUTPUT_SIZE); // 20
    zen::CSHA1 zenSha1Hasher;
    zenSha1Hasher = zenSha1Hasher.Write(reinterpret_cast<const unsigned char*>(filebuffer.data()), filebuffer.size());
    zenSha1Hasher.Finalize(zenSha1Output.data());
    std::cout << "zen SHA-1:       ";
    printShaOut(zenSha1Output);

    //// zen SHA-256 hasher
    std::vector<unsigned char> zenSha256Output(zen::CSHA256::OUTPUT_SIZE); // 32
    zen::CSHA256 zenSha256Hasher;
    zenSha256Hasher = zenSha256Hasher.Write(reinterpret_cast<const unsigned char*>(filebuffer.data()), filebuffer.size());
    zenSha256Hasher.Finalize(zenSha256Output.data());
    std::cout << "zen SHA-256:     ";
    printShaOut(zenSha256Output);

    //// zen SHA-512 hasher
    std::vector<unsigned char> zenSha512Output(zen::CSHA512::OUTPUT_SIZE); // 64
    zen::CSHA512 zenSha512Hasher;
    zenSha512Hasher = zenSha512Hasher.Write(reinterpret_cast<const unsigned char*>(filebuffer.data()), filebuffer.size());
    zenSha512Hasher.Finalize(zenSha512Output.data());
    std::cout << "zen SHA-512:     ";
    printShaOut(zenSha512Output);

    //////////////////

    //// zcash SHA-1 hasher
    std::vector<unsigned char> zcashSha1Output(zcash::CSHA1::OUTPUT_SIZE); // 20
    zcash::CSHA1 zcashSha1Hasher;
    zcashSha1Hasher = zcashSha1Hasher.Write(reinterpret_cast<const unsigned char*>(filebuffer.data()), filebuffer.size());
    zcashSha1Hasher.Finalize(zcashSha1Output.data());
    std::cout << "zcash SHA-1:     ";
    printShaOut(zcashSha1Output);

    //// zcash SHA-256 hasher
    std::vector<unsigned char> zcashSha256Output(zcash::CSHA256::OUTPUT_SIZE); // 32
    zcash::CSHA256 zcashSha256Hasher;
    zcashSha256Hasher = zcashSha256Hasher.Write(reinterpret_cast<const unsigned char*>(filebuffer.data()), filebuffer.size());
    zcashSha256Hasher.Finalize(zcashSha256Output.data());
    std::cout << "zcash SHA-256:   ";
    printShaOut(zcashSha256Output);

    //// zcash SHA-512 hasher
    std::vector<unsigned char> zcashSha512Output(zcash::CSHA512::OUTPUT_SIZE); // 64
    zcash::CSHA512 zcashSha512Hasher;
    zcashSha512Hasher = zcashSha512Hasher.Write(reinterpret_cast<const unsigned char*>(filebuffer.data()), filebuffer.size());
    zcashSha512Hasher.Finalize(zcashSha512Output.data());
    std::cout << "zcash SHA-512:   ";
    printShaOut(zcashSha512Output);

    //////////////////

    bool retVal = false;
    EVP_MD_CTX   *mdctx = nullptr;
    EVP_MD *openssl_sha1_md = nullptr, *openssl_sha256_md = nullptr, *openssl_sha512_md = nullptr;
    unsigned int mdLength = 0;

    mdctx = EVP_MD_CTX_new();
    //// OpenSSL SHA-1 hasher
    std::vector<unsigned char> openSSLSha1Output(EVP_MAX_MD_SIZE);    // 64
    openssl_sha1_md   = EVP_MD_fetch(NULL, "SHA-1",   NULL);                    if (!openssl_sha1_md)   { std::cout << "error 01" << std::endl; std::exit(-1); }
    retVal = EVP_DigestInit_ex2(mdctx, openssl_sha1_md,   NULL);                if (!retVal)            { std::cout << "error 02" << std::endl; std::exit(-1); }
    retVal = EVP_DigestUpdate(mdctx, filebuffer.data(), filebuffer.size());     if (!retVal)            { std::cout << "error 03" << std::endl; std::exit(-1); }
    retVal = EVP_DigestFinal_ex(mdctx, openSSLSha1Output.data(), &mdLength);    if (!retVal)            { std::cout << "error 04" << std::endl; std::exit(-1); }
    openSSLSha1Output.resize(mdLength);
    std::cout << "OpenSSL SHA-1:   ";
    printShaOut(openSSLSha1Output);

    EVP_MD_CTX_reset(mdctx);
    //// OpenSSL SHA-256 hasher
    std::vector<unsigned char> openSSLSha256Output(EVP_MAX_MD_SIZE);  // 64
    openssl_sha256_md = EVP_MD_fetch(NULL, "SHA-256", NULL);                    if (!openssl_sha256_md) { std::cout << "error 05" << std::endl; std::exit(-1); }
    retVal = EVP_DigestInit_ex2(mdctx, openssl_sha256_md, NULL);                if (!retVal)            { std::cout << "error 06" << std::endl; std::exit(-1); }
    retVal = EVP_DigestUpdate(mdctx, filebuffer.data(), filebuffer.size());     if (!retVal)            { std::cout << "error 07" << std::endl; std::exit(-1); }
    retVal = EVP_DigestFinal_ex(mdctx, openSSLSha256Output.data(), &mdLength);  if (!retVal)            { std::cout << "error 08" << std::endl; std::exit(-1); }
    openSSLSha256Output.resize(mdLength);
    std::cout << "OpenSSL SHA-256: ";
    printShaOut(openSSLSha256Output);

    EVP_MD_CTX_reset(mdctx);
    //// OpenSSL SHA-512 hasher
    std::vector<unsigned char> openSSLSha512Output(EVP_MAX_MD_SIZE);  // 64
    openssl_sha512_md = EVP_MD_fetch(NULL, "SHA-512", NULL);                    if (!openssl_sha512_md) { std::cout << "error 09" << std::endl; std::exit(-1); }
    retVal = EVP_DigestInit_ex2(mdctx, openssl_sha512_md, NULL);                if (!retVal)            { std::cout << "error 10" << std::endl; std::exit(-1); }
    retVal = EVP_DigestUpdate(mdctx, filebuffer.data(), filebuffer.size());     if (!retVal)            { std::cout << "error 11" << std::endl; std::exit(-1); }
    retVal = EVP_DigestFinal_ex(mdctx, openSSLSha512Output.data(), &mdLength);  if (!retVal)            { std::cout << "error 12" << std::endl; std::exit(-1); }
    openSSLSha512Output.resize(mdLength);
    std::cout << "OpenSSL SHA-512: ";
    printShaOut(openSSLSha512Output);

    EVP_MD_free(openssl_sha512_md);
    EVP_MD_free(openssl_sha256_md);
    EVP_MD_free(openssl_sha1_md);
    EVP_MD_CTX_free(mdctx);

    return 0;
}