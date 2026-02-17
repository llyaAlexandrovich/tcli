#pragma once



#include <iostream>
#include <string>


#include "td/telegram/Client.h"
#include "td/telegram/td_api.h"
#include "td/telegram/td_api.hpp"


#include "ftxui/dom/elements.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/screen/screen.hpp"


#include "tdhelper/tdtypes.hpp"




class Input
{
public:
    Input()
    {
        InputOptions.content = &InputContent;
        InputOptions.placeholder = InputPlaceHolder;
        InputOptions.transform = [&](ftxui::InputState InputState){
            if(InputState.focused) return InputState.element = ftxui::text(InputContent);
            return InputState.element = ftxui::text(InputPlaceHolder);
        };
    }


    ftxui::InputOption InputOptions = ftxui::InputOption::Spacious();


    void HideInput()
    {
        bShowInput = false;
    }


    void ShowInput()
    {
        bShowInput = true;
    }


private:
    std::string InputContent;
    std::string InputPlaceHolder = "Write a message...";

    bool bShowInput = false;
};
