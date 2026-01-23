#include "config.hpp"













#if defined _WIN32 || defined _WIN64 // Windows
[[nodiscard]]std::vector<HANDLE> LockFiles() noexcept
{

}



[[noreturn]]void ReleaseFiles(std::vector<HANDLE> FileDescriptors) noexcept
{

}



[[noreturn]]void CheckAndCreateRequiredDirictories() noexcept
{
    // NOTE: Despite the function's name we don't really check if directory exists
    // and create it if not. We basically leaning on ERROR_ALREADY_EXISTS error
    // from Windows and trying to create the new directories all the time.
    if(!CreateDirectoryW(L"tdata", NULL))
    {
        if(GetLastError() == 0x183)
        {
            spdlog::info("Directory already exists - /tdata");
        }
    }

    if(!CreateDirectoryW(L"tdata/user_data", NULL))
    {
        if(GetLastError() == 0x183)
        {
            spdlog::info("Directory already exists - /user_data");
        }
    }

    if(!CreateDirectoryW(L"tdata/user_data/cache", NULL))
    {
        if(GetLastError() == 0x183)
        {
            spdlog::info("Directory already exists - /cache");
        }
    }

    if(!CreateDirectoryW(L"tdata/user_data/media_cache", NULL))
    {
        if(GetLastError() == 0x183)
        {
            spdlog::info("Directory already exists - /media_cache");
        }
    }
}


// TODO: i'm not done with understanding configs in telegram this functions is
// TODO: not even under the maintain for now.
[[nodiscard]]bool CheckConfigs() noexcept
{
    //if(!fs::IsFileExists("tdata/"))
}



#else // Linux and others


#endif // Linux
