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
     * @param FileSize  variable to write file size to
     * 
     * @return return either size of the file or 0 in error
     * 
     * @since 1.0.0
     */
    [[noreturn]]void GetFileSize(std::string_view FileName, std::size_t& FileSize) noexcept;



    /**
     * Read entire file.
     * 
     * @author Ilya Alexandrovich
     * 
     * @param FileName  read-only name of the file
     * @param FileContent  buffer to read file data to
     * 
     * @since 1.0.0
    */
    [[noreturn]]void ReadFile(std::string_view FileName, std::string& FileContent) noexcept;



    /**
     * Read part of the file.
     * 
     * @author Ilya Alexandrovich
     * 
     * @param FileName  read-only name of the file
     * @param FileContent  buffer to read file data to
     * @param BytesToRead  number of bytes to read
     * 
     * @since 1.0.0
     */
    [[noreturn]] void ReadFilePart(std::string_view FileName, std::string& FileContent, std::size_t BytesToRead) noexcept;



    /**
     * Search for a file in the current and all included directories.
     * 
     * @author Ilya Alexandrovich
     * 
     * @param FileName  read-only name of the file
     * @param FilePath  variable to store the founded path to 
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
