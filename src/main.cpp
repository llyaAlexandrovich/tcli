#include "main.hpp"








int main(int argc, char **argv)
{   
    // Set console mode to work with UTF-16.
    //_setmode(_fileno(stdout), _O_U16TEXT);


    std::string language_code;
    for(int counter = 1; counter < argc; ++counter)
    {
        std::string_view token(argv[counter]);
        if(token == "-H" || token == "--help")
        {
            std::wcout << HelpPageText << std::endl;
            return 0;
        }
        //else if(token == "-U" || token == "--user")
        //{
        //    user = argv[counter + 1];
        //    ++counter;
        //}
        //else if(token == "--proxy")
        //{
        //    ;
        //}
        else if(token == "-L" || token == "--locale")
        {
            language_code = argv[counter + 1];
            ++counter;
        }
    }


    if(!language_code.empty())
    {
        if(ValidateLanguageCode(language_code))
        {
            LanguageCode = language_code;
        }
    }


    //if(user.empty())
    //{
    //    ;
    //}


    tcli T;
    T.run();



    return 0;
}
