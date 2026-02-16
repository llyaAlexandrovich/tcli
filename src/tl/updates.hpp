#pragma once



#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <unordered_map>
#include <functional>
#include <memory>


#include "td/telegram/Client.h"
#include "td/telegram/td_api.h"
#include "td/telegram/td_api.hpp"


#include "types.hpp"
#include "tdhelper/tdtypes.hpp"




class TelegramUpdates
{
public:
    /**
     * There's quite a lot of updates in Telegram so i decided
     * to manage all of them separately.
     * 
     * @author Ilya Alexandrovich
     * 
     * @param bIsAuthorized  showing whether user is authorized or not
     * @param bIsRestartRequired  showing whether restart is required or not
     * @param Users  map of users
     * @param Chats  map of chats
     * 
     * @since 1.0.0  
     */
    TelegramUpdates(
        bool bIsAuthorized,
        bool bIsRestartRequired,
        std::unordered_map<std::int64_t, td_api::object_ptr<td_api::user>>& Users,
        std::unordered_map<std::int64_t, td_api::object_ptr<td_api::chat>>& Chats)
        :
        bIsAuthorized(bIsAuthorized), bIsRestartRequired(bIsRestartRequired),\
        Users(Users), Chats(Chats)
    {

    }


    /**
     * Process Telegram updates.
     * 
     * @author Ilya Alexandrovich
     * 
     * @param Update  telegram update
     */
    void ProcessUpdate(TdObject Update)
    {

    }

private:
    TdAuthorizationState AuthorizationState;

    bool& bIsAuthorized;
    bool& bIsRestartRequired;

    std::unordered_map<std::int64_t, td_api::object_ptr<td_api::user>>& Users;
    std::unordered_map<std::int64_t, td_api::object_ptr<td_api::chat>>& Chats;
};
