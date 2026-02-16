#pragma once



#include <iostream>
#include <string>
#include <map>
#include <unordered_map>
#include <vector>
#include <functional>
#include <thread>
#include <mutex>


#include "td/telegram/Client.h"
#include "td/telegram/td_api.h"
#include "td/telegram/td_api.hpp"


#include "types.hpp"
#include "tdhelper/tdtypes.hpp"


#include "chats.hpp"
#include "updates.hpp"
#include "query.hpp"



class TelegramCLI : TelegramUpdates
{
public:
    TelegramCLI()
    {
        TC = TelegramChats(ChatsOrder, );
    }


private:
    std::unique_ptr<td::ClientManager> ClientManager;
    std::int32_t ClientId{0};


    bool bIsAuthorized{false};
    bool bIsRestartRequired{false};

    std::uint64_t CurrentQueryID{0};
    std::uint64_t AuthQueryID{0};


    std::unordered_map<std::int64_t, td_api::object_ptr<td_api::user>> Users;
    std::unordered_map<std::uint64_t, std::function<void(TdObject)>> Handlers;
    std::unordered_map<std::int64_t, td_api::object_ptr<td_api::chat>> Chats;

    std::vector<std::int64_t> ChatsOrder;


    TelegramChats TC;

};
