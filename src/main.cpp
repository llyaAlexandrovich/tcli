#include "main.hpp"








int main(int argc, char **argv)
{
    
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


    
}
