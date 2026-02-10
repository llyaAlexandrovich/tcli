#pragma once



#include <iostream>
#include <sstream>
#include <string>
#include <functional>
#include <string_view>
#include <map>
#include <memory>
#include <vector>
#include <codecvt>



#include "src/localization/localization.hpp"


#include "td/telegram/Client.h"
#include "td/telegram/td_api.h"
#include "td/telegram/td_api.hpp"


#include "src/types.hpp"
#include "tdhelper/tdtypes.hpp"








class UIRender
{
public:
    UIRender()
    {
        GetScreenParams();

        stream = std::wstringstream();

        DrawDefaultScreen();
    }


    /**
     * 
     */
    void Render()
    {
        
    }



private:
    // Screen parameters.
    short width{300};
    short height{150};


    // Current console stream.
    std::wstringstream stream;


    // Codecvt object: string => wstring
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;



    /**
     * Set parameters for the current console.
     * 
     * @author Ilya Alexandrovich
     * 
     * @since 1.0.0
     */
    void SetConsoleParams() noexcept
    {
        stream.imbue(std::locale(LocaleIETF.data()));
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
        ClearScreen();
        DrawBorders();
    }



    /**
     * Draw borders.
     * 
     * @author Ilya Alexandrovich
     * 
     * @since 1.0.0
     */
    void DrawBorders()
    {
        // Above border.
        stream << "\x1b[104m"; // Set up blue color.
        for(short counter = 0; counter < width; ++counter) stream << ' ';
        stream << "\x1b[0m" << std::endl; // Reset color scheme.
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
