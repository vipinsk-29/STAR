#include "FC3_FileUtilities.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <memory>
#include <openssl/evp.h>
#include <g3log/g3log.hpp>


/// <summary>
/// 
/// </summary>
/// <param name="hash"></param>
/// <param name="length"></param>
/// <returns></returns>
std::string CCHIL::Star::FC3_FileUtilities::to_hex_string(const unsigned char* hash, unsigned int length) {
    std::stringstream ss;
    for (unsigned int i = 0; i < length; ++i) {
        ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
    }
    return ss.str();
}

/// <summary>
/// 
/// </summary>
/// <param name="filepath"></param>
/// <returns></returns>
std::string CCHIL::Star::FC3_FileUtilities::calculate_file_sha256(const std::filesystem::path& filepath) {
    // Open the file in binary mode
    std::ifstream file(filepath, std::ios::binary);
    if (!file.is_open()) {
        LOG(WARNING) << "Could not open file: " << filepath.string();
        return "";
    }

    // RAII wrapper for the OpenSSL EVP message digest context
    std::unique_ptr<EVP_MD_CTX, decltype(&EVP_MD_CTX_free)> md_context(EVP_MD_CTX_new(), &EVP_MD_CTX_free);
    if (!md_context) {
        LOG(WARNING) << "Failed to create OpenSSL EVP context.";
        return "";
    }

    // Initialize the context to use SHA-256
    if (EVP_DigestInit_ex(md_context.get(), EVP_sha256(), nullptr) != 1) {
        LOG(WARNING) << "Failed to initialize SHA-256 context.";
        return "";
    }

    // Buffer to read chunks (64 KB for optimal OS file cache alignment)
    constexpr size_t buffer_size = 64 * 1024;
    std::vector<char> buffer(buffer_size);

    // Read the file in chunks and stream it into the hash generator
    while (file.good()) {
        file.read(buffer.data(), buffer_size);
        std::streamsize bytes_read = file.gcount();
        if (bytes_read > 0) {
            if (EVP_DigestUpdate(md_context.get(), buffer.data(), bytes_read) != 1) {
                LOG(WARNING) << "Failed to update hash context with file chunk.";
                return "";
            }
        }
    }

    // Finalize the digest and extract the raw bytes
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_length = 0;
    if (EVP_DigestFinal_ex(md_context.get(), hash, &hash_length) != 1) {
        LOG(WARNING) << "Failed to finalize SHA-256 digest.";
        return "";
    }

    return to_hex_string(hash, hash_length);
}

/// <summary>
/// 
/// </summary>
/// <param name="rbsTs"></param>
/// <param name="binFileTimeTs"></param>
/// <returns></returns>
bool CCHIL::Star::FC3_FileUtilities::CheckTimeStamps(uint64_t rbsTs, uint64_t binFileTimeTs) 
{
    constexpr uint64_t netTicksSecond = 10000000ULL;
    constexpr uint64_t DIFF_TICKS_ALLOWED = 90 * netTicksSecond;
    bool retVal = false;

    if (rbsTs == 0)
    {
        LOG(WARNING) << "RBS timestamp not valid";
    }
    if (binFileTimeTs == 0) 
    {
        LOG(WARNING) << "Id defines file timestamp not valid";
    }

    if (rbsTs > 0 && binFileTimeTs > 0) 
    {
        uint64_t diffTicks = (rbsTs > binFileTimeTs) ? (rbsTs - binFileTimeTs) : (binFileTimeTs - rbsTs);

        if (rbsTs > binFileTimeTs) 
        {
			LOG(INFO) << "RBS is newer than s19 file by approx " << diffTicks / netTicksSecond << " seconds";
        }
        else 
        {
			LOG(INFO) << "RBS is older than s19 file by approx " << diffTicks / netTicksSecond << " seconds";
        }

        // Check if timestamp difference is within the acceptable 2-minute window
        if (diffTicks <= DIFF_TICKS_ALLOWED)
        {
			LOG(INFO) << "RBS is in the expected time range, no flash of FC3";
            retVal = true;
        }
        else 
        {
			LOG(INFO) << "Loaded RBS is not fitting! Flash FC3";
        }
    }
    else 
    {
        return retVal;
    }

    return retVal;
}
