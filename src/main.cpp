#include "main.hpp"








int main(int argc, char **argv)
{
    // Logging settings.
    auto root = spdlog::rotating_logger_mt("root", "log.log", MaxLoggerFileSize, MaxNumberOfLoggerFiles);
    spdlog::set_pattern("[%Y-%m-%d %T%z] - %v"); // [2000-12-25 23:50:59+2000] - Logging message
    spdlog::set_level(spdlog::level::info);
    spdlog::set_default_logger(root);

    // Basic log info. Trying to be consistent with Telegram logs.
    spdlog::info("Launched version: {}, install beta: [{}], debug mode: [{}]", NumVersion, IsBeta, DEBUG);
    spdlog::info("Executable dir: {}{}\\, name: {}", std::filesystem::path(argv[0]).root_path(), std::filesystem::path(argv[0]).relative_path(), std::filesystem::path(argv[0]).filename());
    spdlog::info("Initial working dir: {}{}\\", std::filesystem::path(argv[0]).root_path(), std::filesystem::path(argv[0]).relative_path());
    spdlog::info("Command line: {}", argv);
    spdlog::info("Logs started");
    

    std::string User_, Proxy_;
    for(int counter = 1; counter < argc; ++counter)
    {
        std::string_view token(argv[counter]);
        if(token == "-H" || token == "--help")
        {
            std::cout << HelpPage << std::endl;
            return 0;
        }
        else if(token == "-U" || token == "--user")
        {
            ;
        }
        else if(token == "--proxy")
        {
            ;
        }
    }

    

    std::map<std::string, std::string> EnvContent;
    
}
