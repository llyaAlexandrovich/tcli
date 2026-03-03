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
#include "auth_updates.hpp"
#include "updates.hpp"


#include "render/ui/ui_render.hpp"


// Telegram related consts.

// Telegram API ID.
static int const ApiID = 2326009;

// Telegram API hash.
static std::string const ApiHash = "82a7161dfbea98eeb6fafa420e2fb6a2";


// Recieve TimeOut.
static double const TimeOut = 10.0;


// User states.
// Directory to store data to.
static std::string const DataDirectory = "tdata";

// Whether to use caching or not.
static bool const bUseCache = true;

// Whether to support secret chats or not.
static bool const bSupportSecretChats = true;

// Device model.
static std::string const DeviceModel = "Desktop";







class TelegramCLI : public TelegramChats<TelegramCLI>, public TelegramUpdates<TelegramCLI>, public TelegramAuthUpdates<TelegramCLI>,  public UIRender
{
public:
    TelegramCLI()
    {
        // Basic TdLib initialization.
        td::ClientManager::execute(td_api::make_object<td_api::setLogVerbosityLevel>(1));
        ClientManager = std::make_unique<td::ClientManager>();
        ClientID = ClientManager->create_client_id();
        SendQuery(td_api::make_object<td_api::getOption>("version"), {});
        
        // TelegramClI initialization.

        // Should be initialized first because updates are 
        // on their way since yesterday.
        // It will initialize every single update handlers.
        InitTelegramUpdates();

        InitTelegramChats();
    }


    bool run()
    {
        while(true)
        {
            if(bIsRestartRequired)
            {
                return false;
            }
            else if(!bIsAuthorized)
            {
                ProcessResponse(ClientManager->receive(TimeOut));
            }
            else
            {
                // Chat processor should be placed here.
                // UI.Render();
            }
        }
    }


private:
    friend class TelegramChats<TelegramCLI>;
    friend class TelegramUpdates<TelegramCLI>;
    friend class TelegramAuthUpdates<TelegramCLI>;

    std::unique_ptr<td::ClientManager> ClientManager;
    std::int32_t ClientID{0};


    bool bIsAuthorized{false};
    bool bIsRestartRequired{false};

    std::uint64_t CurrentQueryID{0};


    std::unordered_map<std::int64_t, td_api::object_ptr<td_api::user>> Users;
    std::unordered_map<std::uint64_t, std::function<void(TdObject)>> Handlers;
    std::unordered_map<std::int64_t, td_api::object_ptr<td_api::chat>> Chats;

    std::vector<std::int64_t> ChatsOrder{CHAT_LIST_LENGTH};



    [[nodiscard]] std::uint64_t NextQueryID()
    {
        return ++CurrentQueryID;
    }


    /**
     * Send required method call to the query.
     * 
     * @param Function  required method
     * @param Handler  callback function
     * 
     * @since 1.0.0
     */
    void SendQuery(td_api::object_ptr<td_api::Function> Function, std::function<void(TdObject)> Handler)
    {
        auto QueryID = NextQueryID();
        if(Handler)
        {
            Handlers.emplace(QueryID, std::move(Handler));
        }

        ClientManager->send(ClientID, QueryID, std::move(Function));
    }


    /**
     * Process TdLib response(ClientManager->recieve()).
     * 
     * @param Response  TdLib response
     * 
     * @since 1.0.0
     */
    void ProcessResponse(td::ClientManager::Response Response)
    {
        if(!Response.object)
        {
            return;
        }

        if(Response.request_id == 0) // Server response.
        {
            return ProcessUpdate(std::move(Response.object));
        }

        auto it = Handlers.find(Response.request_id);
        if(it != Handlers.end())
        {
            it->second(std::move(Response.object));
            Handlers.erase(it);
        }
    }

}; // class TelegramCLI
