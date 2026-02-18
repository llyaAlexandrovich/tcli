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




class Chat
{
public:
    Chat()
    {
        PlaceHolderChatComponent = ftxui::Renderer([&]{
            return ftxui::text(ChatPlaceHoleder) | ftxui::center;
        });

        ChatComponent = PlaceHolderChatComponent;
    }


    /**
     * Initialize chat content component.
     * 
     * @author ILya Alexandrovich
     * 
     * @param Messages  messages to display
     * 
     * @since 1.0.0
     */
    void initializeChatContent(td_api::object_ptr<td_api::messages> Messages)
    {

    }


    /**
     * Update current chat with additional messages.
     * 
     * @author Ilya Alexandrovich
     * 
     * @param Messages  messages to add to the current chat
     * 
     * @since 1.0.0
     */
    void UpdateChatContent(td_api::object_ptr<td_api::messages> Messages)
    {
        
    }


    /**
     * Clear current chat content.
     * 
     * @author Ilya Alexandrovich
     * 
     * @since 1.0.0
     */
    void ClearChatContent()
    {
        ChatComponent = PlaceHolderChatComponent;
    }

    ftxui::Component ChatComponent;

private:
    ftxui::Component PlaceHolderChatComponent;
    std::string ChatPlaceHoleder = "Select a chat to start messaging";
};
