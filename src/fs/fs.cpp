#include "fs.hpp"







namespace fs
{
    std::size_t GetFileSize(std::string_view FileName) noexcept
    {
        std::error_code ec;
        return std::filesystem::file_size(FileName, ec);
    }



    std::string ReadFile(std::string_view FileName) noexcept
    {
        std::ifstream FileStream(FileName.data());
        std::string output;

        if(!FileStream.is_open())
        {
            return output;
        }

        while(std::getline(FileStream, output));

        FileStream.close();

        return output;
    }



    std::string FindFile(std::string_view FileName) noexcept
    {
        for(const auto& entry: std::filesystem::recursive_directory_iterator(std::filesystem::current_path()))
        {
            if(entry.is_regular_file() && entry.path().filename() == FileName)
            {
                return entry.path().string();
            }
        }
    }
}
