#pragma once



#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <map>
#include <memory>
#include <vector>



#include "../../localization/localization.hpp"





class UIRender
{
public:
    UIRender()
    {
        GetScreenParams();

        std::string locale = GetSystemLocaleWide();
        if(!locale.empty())
        {
            _locale = locale;
        }

        stream = std::stringstream();


    }



private:
    // Screen parameters.
    short width{300};
    short height{150};


    // Console locale.
    std::string _locale{"en_US.UTF-8"};


    // Current console stream.
    std::stringstream stream;


    /**
     * Set parameters for the current console.
     * 
     * @author Ilya Alexandrovich
     * 
     * @since 1.0.0
     */
    void SetConsoleParams() noexcept
    {
        stream.imbue(std::locale(_locale.data()));
    }



    /**
     * Make the screen blank.
     * 
     * @author Ilya Alexandrovich
     * 
     * @since 1.0.0
     */
    void ClearScreen() noexcept
    {
        stream.flush();
    }



    /**
     * Draw default screen.
     * 
     * @author Ilya Alexandrovch
     * 
     * @since 1.0.0
     */
    void DrawDefaultScreen()
    {

    }


#if defined _WIN32 || defined _WIN64 // Windows.
#include <windows.h>

    /**
     * Get parametrs of the current console screen.
     * 
     * @author Ilya Alexandrovich
     * 
     * @since 1.0.0
     */
    void GetScreenParams() noexcept
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        if(GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi))
        {
            width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
            height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
        }
    }


#else // Linux and others.
#include <sys/ioctl.h>
#include <unistd.h>

    /**
     * Get parametrs of the current console screen.
     * 
     * @author Ilya Alexandrovich
     * 
     * @since 1.0.0
     */
    void GetScreenParams() noexcept
    {
        struct winsize w;
        if(!ioctl(STDOUT_FILENO, TIOCGWINSZ, &w)))
        {
            width = w.ws_col;
            height = w.ws_row;
        }
    }


#endif // Linux and others.

};
