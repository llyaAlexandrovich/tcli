#include "fs.hpp"







namespace fs
{
    [[noreturn]]void GetFileSize(std::string_view FileName, std::size_t& FileSize) noexcept
    {
        std::error_code ec;
        FileSize = std::filesystem::file_size(FileName, ec);
    }



    [[noreturn]]void ReadFile(std::string_view FileName, std::string& FileContent) noexcept
    {
        std::ifstream FileStream(FileName.data());

        if(!FileStream.is_open())
        {
            return;
        }

        while(std::getline(FileStream, FileContent));

        FileStream.close();
    }



    [[noreturn]] void ReadFilePart(std::string_view FileName, std::string& FileContent, std::size_t BytesToRead) noexcept
    {
        std::ifstream FileStream(FileName.data());

        if(!FileStream.is_open())
        {
            return;
        }

        FileStream.read(FileContent.data(), BytesToRead);

        FileStream.close();
    }



    [[noreturn]]void FindFile(std::string_view FileName, std::string& FilePath) noexcept
    {
        for(const auto& entry: std::filesystem::recursive_directory_iterator(std::filesystem::current_path()))
        {
            if(entry.is_regular_file() && entry.path().filename() == FileName)
            {
                FilePath = entry.path().string();
            }
        }
    }


    [[nodiscard]]bool IsFileExists(std::string_view FileName) noexcept
    {
        if(std::filesystem::exists(FileName))
        {
            return true;
        }
        return false;
    }



    [[nodiscard]]std::string GetCurrentDir() noexcept
    {
        return std::filesystem::current_path().string();
    }
}
