#include "main.hpp"








int main(int argc, char **argv)
{   
    std::string language_code;
    for(int counter = 1; counter < argc; ++counter)
    {
        std::string_view token(argv[counter]);
        if(token == "-H" || token == "--help")
        {
            std::cout << HelpPageText << std::endl;
            return 0;
        }
        else if(token == "-L" || token == "--locale")
        {
            language_code = argv[counter + 1];
            ++counter;
        }
    }


    while(true)
    {
        std::unique_ptr<TelegramCLI> T = std::make_unique<TelegramCLI>();
        if(!T->run())
        {
            T = std::make_unique<TelegramCLI>();
        }
        else break;
    }


    return 0;
}
