#include "main.hpp"








int main(int argc, char **argv)
{
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
    LoadEnvVariables(_EnvFileName, EnvContent);
}
