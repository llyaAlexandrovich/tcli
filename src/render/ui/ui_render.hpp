#pragma once



#include <iostream>
#include <sstream>
#include <string>
#include <functional>
#include <algorithm>
#include <string_view>
#include <map>
#include <memory>
#include <vector>
#include <codecvt>



#include "src/localization/localization.hpp"


#include "td/telegram/Client.h"
#include "td/telegram/td_api.h"
#include "td/telegram/td_api.hpp"


#include "ftxui/dom/elements.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/screen/screen.hpp"


#include "src/types.hpp"
#include "tdhelper/tdtypes.hpp"


#include "place_holders.hpp"
#include "status_bar.hpp"







class UIRender : PlaceHolder : StatusBar : Chat
{
public:
    UIRender() : StatusBar()
    {
        Screen = ftxui::ScreenInteractive::FullScreen();
    }



private:
    // Screen.
    ftxui::ScreenInteractive Screen;


    // Chat.
    ftxui::Component BlankChat = ftxui::Renderer([&]{
        return ftxui::text(ChatPlaceHolder) | ftxui::center;
    });
    ftxui::Component Chat = BlankChat;


    // Input content.
    std::string InputContent;
    

    // Input options.
    ftxui::InputOption InputOptions = ftxui::InputOption::Spacious();
    InputOptions.content = &InputContent;
    InputOptions.placeholder = InputPlaceHolder;

    // Input transform.
    InputOptions.transform = [&](ftxui::InputState InputState){
        if(InputState.focused) return InputState.element = ftxui::text(InputContent);
        return InputState.element = ftxui::text(InputPlaceHolder);
    };

    // Input.
    bool ShowInput = false;
    ftxui::Component Input = ftxui::Maybe(ftxui::Input(InputOptions) | ftxui::border, &ShowInput);


    // Chat selector.
    int SelectedChat{0};

    ftxui::MenuOption ChatSelectorOptions{
        .on_enter = [&]{
            ShowInput = true;
            Chat = ftxui::Renderer([&]{
                // Chat rendering should be here.
            });
        }
    };

    ftxui::Component ChatSelector = ftxui::Menu() | ftxui::frame | ftxui::vscroll_indicator;
};
