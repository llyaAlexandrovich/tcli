#include "dotenv.hpp"








[[nodiscard]]void LoadEnvVariables(std::string_view FileName, std::map<std::string, std::string> EnvContent) noexcept
{
    std::string FileContent;
    fs::ReadFile(FileName, FileContent);
    FileContent.shrink_to_fit();


    std::istringstream stream(FileContent);
    convenient_string string;
    while(stream >> string)
    {
        std::vector<std::string> tokens = string.extern_split('=');
        EnvContent[tokens[0]] = tokens[1];
    }
}
