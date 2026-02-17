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




class Menu
{
public:
    Menu();


    void InitMenu(td_api::object_ptr<td_api::chats> Chats)
    {

    }


    int SelectedChat{0};
private:
    
};
