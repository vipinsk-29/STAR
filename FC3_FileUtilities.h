/******************************************************************/
/* FILE: CCHIL.Star.FC3_FileUtilities.h
/* SW-COMPONENT: C++-genericToolChainModelComponent
/* DESCRIPTION: Source is used to build a Labcar model component for a generic ToolChain, based on C++ code
/* COPYRIGHT: (C) 2026 Robert Bosch GmbH
/*
/* The reproduction, distribution and utilization of this file as
/* well as the communication of its contents to others without express
/* authorization is prohibited. Offenders will be held liable for the
/* payment of damages. All rights reserved in the event of the grant
/* of a patent, utility model or design.
/******************************************************************/

#pragma once
#include <string>
#include <cstdint>
#include <filesystem>
//#include "FC3_CardHandling.h"

//conditional include for SHA256 calculation
#if defined(_WIN32) || defined(_WIN64) 
	#include <openssl/evp.h>
#else // HiL
	#include <openssl/evp.h>
#endif

namespace CCHIL
{
    namespace Star
    {
        class FC3_FileUtilities
        {
        public:
            /**
             * @brief Computes the SHA-256 hash of a file.
             * @param filepath Path to the target file.
             * @return Hexadecimal hash string on success, or an empty string on error.
             */
            static std::string calculate_file_sha256(const std::filesystem::path& filepath);

            /**
             * @brief Compares two timestamps (represented in .NET Ticks: 100-nanosecond intervals).
             * @param rbsTs Timestamp retrieved from the RBS.
             * @param binFileTimeTs Timestamp retrieved from the binary/s19 file.
             * @return true if timestamps are identical, false otherwise.
             */
            static bool CheckTimeStamps(uint64_t rbsTs, uint64_t binFileTimeTs);

        private:
            /// @brief Helper function to convert raw byte array to a hex string representation.
            static std::string to_hex_string(const unsigned char* hash, unsigned int length);
        };
    }
}