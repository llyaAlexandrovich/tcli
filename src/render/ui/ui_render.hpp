#pragma once



#include <iostream>
#include <string>


#include "localization/localization.hpp"


#include "td/telegram/Client.h"
#include "td/telegram/td_api.h"
#include "td/telegram/td_api.hpp"


#include "ftxui/dom/elements.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/screen/screen.hpp"


#include "types.hpp"
#include "tdhelper/tdtypes.hpp"


#include "chat.hpp"
#include "status_bar.hpp"
#include "input.hpp"







class UIRender : StatusBar, Chat, Input
{
public:
    UIRender()
    {
        
    }


    enum class SceneType : int
    {
        
    };

    void RenderScene()
    {

    }



private:
    // Screen.
    ftxui::ScreenInteractive Screen = ftxui::ScreenInteractive::Fullscreen();


    ftxui::MenuOption ChatSelectorOptions{
        .on_enter = [&]{
            ShowInput();
            
        }
    };

    ftxui::Component ChatSelector = ftxui::Menu() | ftxui::frame | ftxui::vscroll_indicator;
};
