#pragma once



#include <iostream>
#include <string>
#include <string_view>
#include <vector>

#include "fs/fs.hpp"









[[nodiscard]]std::vector<bool> Configure() noexcept;



#if defined _WIN32 || defined _WIN64 // Windows
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <fileapi.h>

/**
 * Out configs should not be rewritten while we trying to read them so
 * we lock all required configs before processing each of them.
 * 
 * @author Ilya Alexandrovich
 * 
 * @since 1.0.0
 */
[[nodiscard]] std::vector<HANDLE> LockFiles() noexcept;



/**
 * Release the previously locked files.
 * 
 * @author Ilya Alexandrovich
 * 
 * @param FileDescriptors  list of descriptors of all previously locked files
 * 
 * @since 1.0.0
 */
[[noreturn]] void ReleaseFiles(std::vector<HANDLE> FileDescriptors) noexcept;


/**
 * Check whether required directories exists and create them if not.
 * 
 * @author Ilya Alexandrovich
 * 
 * @since 1.0.0
 */
[[noreturn]] void CheckAndCreateRequiredDirictories() noexcept;



/**
 * Check whether all required configs exists and configured.
 * 
 * @author Ilya Alexandrovich
 * 
 * @return return whether true if all configs exist and configured or false
 * 
 * @since 1.0.0
 */
[[nodiscard]] bool CheckConfigs() noexcept;



[[nodiscard]] 

#else // Linux and others



#endif // Linux
