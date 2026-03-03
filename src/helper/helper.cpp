#include "helper.hpp"








[[nodiscard]] int CalculateVersion(std::string StringVersion) noexcept
{
    int output = 0;
    for(const auto& symbol : StringVersion)
    {
        output += (int)symbol;
    }
    return output - (0x2e * 2); // Subtract a value of two dots '.' from the result.
}



[[nodiscard]] int GetMajorVersion(std::string StringVersion) noexcept
{
    StringVersion.erase(StringVersion.find('.'), StringVersion.length() - StringVersion.find('.'));
    return std::stoi(StringVersion);
}



[[nodiscard]] int GetMinorVersion(std::string StringVersion) noexcept
{
    StringVersion.erase(0, StringVersion.find('.'));
    StringVersion.erase(StringVersion.find('.'), StringVersion.length() - StringVersion.find('.'));
    return std::stoi(StringVersion);
}



[[nodiscard]] int GetPatchVersion(std::string StringVersion) noexcept
{
    StringVersion.erase(0, StringVersion.find('.'));
    StringVersion.erase(0, StringVersion.find('.'));
    return std::stoi(StringVersion);
}


[[nodiscard]] bool ValidateLanguageCode(std::string& locale) noexcept
{
    // Only 2 languages has support for now.
    // ISO 639-1 language codes.
    if(locale == "ru") return true;
    else if(locale == "en") return true;
    else return false;
}
