#include "config.hpp"








[[nodiscard]]bool IsConfigsExists(std::vector<std::string> ConfigsNames) noexcept
{
    for(const auto& ConfigName : ConfigsNames)
    {
        
    }
}



#if defined _WIN32 || defined _WIN64 // Windows
[[nodiscard]]std::vector<HANDLE> LockFiles() noexcept
{

}



[[noreturn]]void AcquireFiles(std::vector<HANDLE> FileDescriptors) noexcept
{

}



[[nodiscard]]std::vector<std::string> CheckAndCreateRequiredDirictories() noexcept
{
    // NOTE: Despite the function's name we don't really check if directory exists
    // and create it if not. We basically leaning on ERROR_ALREADY_EXISTS error
    // from Windows and trying to create the new directories all the time.
    if(!CreateDirectoryW(L"tdata", NULL))
    {
        if(GetLastError() == 0x183)
        {
            
        }
    }

}



#else // Linux and others


#endif // Linux
