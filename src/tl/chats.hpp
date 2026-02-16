#pragma once



#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <functional>
#include <memory>


#include "td/telegram/Client.h"
#include "td/telegram/td_api.h"
#include "td/telegram/td_api.hpp"


#include "types.hpp"
#include "tdhelper/tdtypes.hpp"





class TelegramChats
{
public:
    /**
     * Get all available chats from local cache. I'm doing this so user wouldn't
     * see just the blank screen thinking something worng is going on.
     * 
     * @author Ilya Alexandrovich
     * 
     * @param Chats  vector to save chat list to
     * @param SendQuery  funciton to call for updates
     * 
     * @since 1.0.0
     */
    TelegramChats(std::vector<std::int64_t>& Chats, TdSendQuery SendQuery)
    {
        SendQuery(td_api::make_object<td_api::getChats>(nullptr, CHATS_TO_LOAD), [&](TdObject Object){
            if(Object->get_id() == td_api::error::ID) return;
            Chats = std::move(td::move_tl_object_as<td_api::chats>(Object)->chat_ids_);
        });
    }


    /**
     * This function required for chats update. This one will make TdLib to go to the
     * remote Telegram server and fetch the chats info.
     * 
     * @author Ilya Alexandrovich
     * 
     * @param SendQuery  funciton to call for updates
     */
    void UpdateChats(TdSendQuery SendQuery)
    {
        SendQuery(td_api::make_object<td_api::loadChats>(nullptr, CHATS_TO_LOAD), [&](TdObject Object){
            if(Object->get_id() == td_api::ok::ID) return;
        });
    }


    /**
     * Funciton for processing 'updateChatPosition' TdLib update.
     * 
     * @author Ilya Alexandrovich
     * 
     * @param Chats  vector to save updated chat list
     * 
     * @since 1.0.0
     */
    void ProcessChatUpdate(std::vector<std::int64_t>& Chats)
    {
        
    }
};
