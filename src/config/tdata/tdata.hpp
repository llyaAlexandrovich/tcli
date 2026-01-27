#pragma once



#include <iostream>
#include <cstdint>
#include <cstddef>
#include <string>
#include <string_view>


#include "fs/fs.hpp"
#include "spdlog/spdlog.h"


/**
 * Concept
 * [magic bytes](4)-[version](4)
 */



/**
 * Check whether file is valid TDF format.
 * 
 * @author Ilya Alexandrovich
 * 
 * @param FileContent  file buffer
 * 
 * @return return whether true if file is valid or false
 * 
 * @since 1.0.0
 */
[[nodiscard]] bool IsValidTDF(std::string& const FileContent) noexcept;



/**
 *  Read and examine TDF config.
 * 
 * @author Ilya Alexandrovich
 * 
 * @param FileName  read-only name of the file
 * @param FileContent  buffer to read config to
 * 
 * @since 1.0.0
 */
[[noreturn]] void ReadTDFConfig(std::string_view FileName, std::string& FileContent) noexcept;



/**
 * 
 */
typedef struct _TDF
{
    std::uint32_t version;
    std::byte PartialMD5;
    bool IsMD5Correct;
    std::shared_ptr<std::string> data;
} TDF;
