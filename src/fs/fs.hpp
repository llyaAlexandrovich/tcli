#pragma once



#include <iostream>
#include <string>
#include <string_view>
#include <filesystem>
#include <fstream>





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
    [[noreturn]]void GetFileSize(std::string_view FileName, std::size_t& FileSize) noexcept;



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
    [[noreturn]]void ReadFile(std::string_view FileName, std::string& FileContent) noexcept;



    /**
     * Search for a file in the current and all included directories.
     * 
     * @author Ilya Alexandrovich
     * 
     * @param FileName  read-only name of the file
     * 
     * @return return either file content or std::string.empty() == true
     * 
     * @since 1.0.0
     */
    [[noreturn]]void FindFile(std::string_view FileName, std::string& FilePath) noexcept;



    /**
     * Check whether file exists or not.
     * 
     * @author Ilya Alexandrovich
     * 
     * @param FileName  read-only name of the file
     * 
     * @return returh either true if file exists or false
     * 
     * @since 1.0.0
     */
    [[nodiscard]]bool IsFileExists(std::string_view FileName) noexcept;



    /**
     * Get current directory.
     * 
     * @author Ilya Alexandrovich
     * 
     * @return return current directory
     * 
     * @since 1.0.0
     */
    [[nodiscard]]std::string GetCurrentDir() noexcept;
}
