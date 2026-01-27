#include "tdata.hpp"








[[nodiscard]] bool IsValidTDF(std::string& const FileContent) noexcept
{
    // This might seem to be pretty stupid but here we are.
    if(FileContent[0] == 'T' && FileContent[1] == 'D' &&\
        FileContent[2] == 'F' && FileContent[3] == '$')
    {
        return true;
    }
    return false;
}



[[noreturn]]void ReadTDFConfig(std::string_view FileName, std::string& FileContent) noexcept
{
    
}
