#pragma once



#include <iostream>
#include <string>
#include <string_view>
#include <vector>

#include "fs/fs.hpp"
#include "spdlog/spdlog.h"



[[nodiscard]]bool IsConfigsExists(std::vector<std::string> ConfigsNames) noexcept;



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
[[nodiscard]]std::vector<HANDLE> LockFiles() noexcept;



/**
 * 
 */
[[noreturn]]void AcquireFiles(std::vector<HANDLE> FileDescriptors) noexcept;


/**
 * 
 */
[[nodiscard]]std::vector<std::string> CheckAndCreateRequiredDirictories() noexcept;

#else // Linux and others



#endif // Linux