#pragma once



#include <iostream>
#include <string>
#include <string_view>
#include <filesystem>
#include <fstream>
#include <exception>


#include "spdlog/spdlog.h"

/**
 * Internal filesystem namespace.
 * 
 * @author Ilya Alexandrovich
 * 
 * @since 1.0.0
 */
namespace fs
{
    /**
     * Get size of the file.
     * 
     * @author Ilya Alexandrovich
     * 
     * @param FileName  read-only name of the file
     * 
     * @return return either size of the file or 0 in error
     * 
     * @since 1.0.0
     */
    std::size_t GetFileSize(std::string_view FileName) noexcept;



    /**
     * Read entire file and return file content.
     * 
     * @author Ilya Alexandrovich
     * 
     * @param FileName  read-only name of the file
     * 
     * @return return either file content or std::string.empty() == true
     * 
     * @since 1.0.0
    */
    std::string ReadFile(std::string_view FileName) noexcept;



    /**
     * Search for a file in the current and all included directories.
     * 
     * @author Ilya Alexandrovich
     * 
     * @param FileName read-only name of the file
     * 
     * @return return either file content or std::string.empty() == true
     * 
     * @since 1.0.0
     */
    std::string FindFile(std::string_view FileName) noexcept;
}
