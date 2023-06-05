#include "digest.hpp"

namespace openssl
{
    DigestBase::DigestBase(const char *name) : digest_{EVP_get_digestbyname(name)}, digest_context_{EVP_MD_CTX_new()}
    {
        if (!digest_)
        {
            throw std::runtime_error("Failed to initialize digest");
        }
        EVP_DigestInit_ex(digest_context_, digest_, nullptr);
    }

    DigestBase &DigestBase::Reset()
    {
        EVP_DigestInit_ex(digest_context_, nullptr, nullptr);
        ingested_size_ = 0;
        return *this;
    }

    DigestBase &DigestBase::Write(const unsigned char *data, size_t len)
    {
        ingested_size_ += len;
        EVP_DigestUpdate(digest_context_, data, len);
        return *this;
    }

    void DigestBase::Finalize(unsigned char output[]) { EVP_DigestFinal_ex(digest_context_, output, nullptr); }
}