#include "main.hpp"








int main(int argc, char **argv)
{   
    std::string locale, user;
    for(int counter = 1; counter < argc; ++counter)
    {
        std::string_view token(argv[counter]);
        if(token == "-H" || token == "--help")
        {
            std::cout << HelpPageText << std::endl;
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
            locale = argv[counter + 1];
            ++counter;
        }
    }


    if(!locale.empty())
    {
        _locale = locale;
    }


    //if(user.empty())
    //{
    //    ;
    //}


    tcli T;
    T.run();



    return 0;
}
