#pragma once

#include <vector>
#include <stdexcept>
#include <openssl/evp.h>

namespace openssl
{

    class CSHA1;
    class CSHA256;
    class CSHA512;

    class DigestBase
    {
    public:
        DigestBase(const char *name);

        virtual ~DigestBase() { EVP_MD_CTX_free(digest_context_); };
        DigestBase(DigestBase &other) = delete;
        DigestBase(DigestBase &&other) = delete;
        DigestBase &operator=(const DigestBase &other) = delete;

        DigestBase &Reset();

        DigestBase &Write(const unsigned char *data, size_t len);

        void Finalize(unsigned char output[]);

    private:
        friend class CSHA1;
        friend class CSHA256;
        friend class CSHA512;
        const EVP_MD *digest_{nullptr};       // The digest function
        EVP_MD_CTX *digest_context_{nullptr}; // The digest context
        size_t digest_size_{0};               // The size of the digest
        size_t ingested_size_{0};             // Number of bytes ingested
    };

    class CSHA1 : public DigestBase
    {
    public:
        CSHA1() : DigestBase("SHA1") {}
    };

    class CSHA256 : public DigestBase
    {
    public:
        CSHA256() : DigestBase("SHA256") {}
    };

    class CSHA512 : public DigestBase
    {
    public:
        CSHA512() : DigestBase("SHA512") {}
    };

} // namespace openssl
