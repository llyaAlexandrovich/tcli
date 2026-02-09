#pragma once



#include <iostream>
#include <sstream>
#include <string>
#include <string_view>
#include <map>
#include <memory>
#include <vector>
#include <codecvt>



#include "../../localization/localization.hpp"


#include "td/telegram/Client.h"
#include "td/telegram/td_api.h"
#include "td/telegram/td_api.hpp"



#include "tdhelper/tdtypes.hpp"





/**
 * UI Renderer class.
 * 
 * @author Ilya Alexandrovich
 * 
 * 
 */
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

        stream = std::wstringstream();
        


        DrawDefaultScreen();

        DrawMainContent();
    }


    void Render()
    {

    }



private:
    // Screen parameters.
    short width{300};
    short height{150};


    // Console locale.
    std::string _locale{"en_US.UTF-8"};


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



    /**
     * Draw chat(main) content;
     * 
     * @author Ilya Alexandrovich
     * 
     * 
     */
    void DrawMainContent(td::tl_object_ptr<td_api::chats> chats, td::)
    {

    }



    /**
     * 
     */
    std::string_view ShowChatUnit(td_api::object_ptr<td_api::chat> chat, td_api::object_ptr<td_api::message> message, td_api::object_ptr<td_api::user> user)
    {
        std::wstring output;
        td_api::downcast_call(*message->sender_id_,
            overloaded(
                [&](td_api::messageSenderUser& user)
                {
                    
                },
                [&](td_api::messageSenderChat& chat)
                {
                    output = GROUP_CHAT_PREFIX;
                    
                }
        ));

        output += converter.from_bytes(chat->title_.data());
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
