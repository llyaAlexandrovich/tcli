#pragma once



#include <iostream>
#include <string>
#include <locale>




#if defined _WIN32 || defined _WIN64
#include <windows.h>
#include <codecvt>

/**
 * Get system locale.
 * 
 * @author Ilya Alexandrovich
 * 
 * @return whether system locale or std::string.empty()
 * 
 * @since 1.0.0
 */
[[nodiscard]] std::string GetSystemLocale() noexcept
{
    std::wstring WinLocaleName;

    if(GetUserDefaultLocaleName(WinLocaleName.data(), LOCALE_NAME_MAX_LENGTH) == 0)
    {
        return std::string();
    }

    // !NOTE: This function is deprecated since cxx17.
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::string output = converter.to_bytes(WinLocaleName);
    output.erase(2, output.length() - 2);

    return output;
}



/**
 * Get system locale as is using IETF standard.
 * 
 * @author Ilya Alexandrovich
 * 
 * @return whether system locale or std::string.empty()
 * 
 * @since 1.0.0
 */
[[nodiscard]] std::string GetSystemLocaleWide() noexcept
{
    std::wstring WinLocaleName;

    if(GetUserDefaultLocaleName(WinLocaleName.data(), LOCALE_NAME_MAX_LENGTH) == 0)
    {
        return std::string();
    }

    // !NOTE: This function is deprecated since cxx17.
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::string output = converter.to_bytes(WinLocaleName);

    return output;
}



#else // Linux and others.
#include <clocale>

/**
 * Get system locale.
 * 
 * @author Ilya Alexandrovich
 * 
 * @return whether system locale or std::string.empty()
 * 
 * @since 1.0.0
 */
[[nodiscard]] std::string GetSystemLocale() noexcept
{
    const char* LinuxLocaleName = std::setlocale(LC_ALL, "");
    if(LinuxLocaleName != nullptr)
    {
        std::string output(LinuxLocaleName);
        output.erase(2, output.length() - 2);
        return output;
    }
    return std::string();
}



/**
 * Get system locale as is using IETF standard.
 * 
 * @author Ilya Alexandrovich
 * 
 * @return whether system locale or std::string.empty()
 * 
 * @since 1.0.0
 */
[[nodiscard]] std::string GetSystemLocaleWide() noexcept
{
    const char* LinuxLocaleName = std::setlocale(LC_ALL, "");
    if(LinuxLocaleName != nullptr)
    {
        std::string output(LinuxLocaleName);
        return output;
    }
    return std::string();
}

#endif // Linux and others.
