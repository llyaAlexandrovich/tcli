#pragma once



#include <iostream>
#include <functional>
#include <string>
#include <format>
#include <thread>
#include <map>



#include "helper/helper.hpp"
#include "localization/localization.hpp"


#include "spdlog/spdlog.h"
#include "spdlog/sinks/rotating_file_sink.h"


#include "td/telegram/Client.h"
#include "td/telegram/td_api.h"
#include "td/telegram/td_api.hpp"



// !NOTE: -U, --proxy tokens are not supported yet.
/**
 * Recognizable arguments.
 * NONE => run program with the default settings
 * -H --help => show help page and exit
 * -U --user => specify the user for login
 * -L --locale => specify locale
 * --proxy => specify proxy settings
 */
int main(int argc, char **argv);


// Version of TCli.
static std::string const VersionAsString = "1.0.0";
static int const VersionAsInt = CalculateVersion(VersionAsString);
static short const VersionAsIntMajor = (short)GetMajorVersion(VersionAsString);
static short const VersionAsIntMinor = (short)GetMinorVersion(VersionAsString);
static short const VersionAsIntPatch = (short)GetPatchVersion(VersionAsString);


// Telegram API ID.
static int const ApiID = 2326009;

// Telegram API hash.
static std::string const ApiHash = "82a7161dfbea98eeb6fafa420e2fb6a2";


// Recieve TimeOut.
static double const TimeOut = 10.0;


// Help page content.
static std::string const HelpPageText = std::format("TCli v{} by Ilya Alexandrovich", VersionAsString);


// This number represents 10MB using Mib IEC system(2^20 * 10).
static int const MaxLoggerFileSize = 10485760;


// This number represents the maximum number of log files.
static int const MaxNumberOfLoggerFiles = 1;


// Indicates whether beta version is installed.
static bool const IsBeta = false;


// Debug.
#ifndef DEBUG
#define NDEBUG
#define DEBUG false
#endif


// User states.
// User's system locale.
static std::string _locale = "en"; // Default locale.

// Directory to store data to.
static std::string const DataDirectory = "tdata";

// Whether to use caching or not.
static bool const bUseCache = true;

// Whether to support secret chats or not.
static bool const bSupportSecretChats = true;

// Device model.
static std::string const DeviceModel = "Desktop";



// Type Dispatching.
namespace detail {
template <class... Fs>
struct overload;


template <class F>
struct overload<F> : public F {
    explicit overload(F f) : F(f) {
}
};


template <class F, class... Fs>
struct overload<F, Fs...> : public overload<F>, public overload<Fs...> {
    overload(F f, Fs... fs) : overload<F>(f), overload<Fs...>(fs...) {}
    using overload<F>::operator();
    using overload<Fs...>::operator();
};

}  // namespace detail


template <class... F>
auto overloaded(F... f) {
    return detail::overload<F...>(f...);
}


namespace td_api = td::td_api;


/**
 * Basic program class.
 * 
 * 
 * 
 */
class tcli
{
public:
    tcli()
    {
        td::ClientManager::execute(td_api::make_object<td_api::setLogVerbosityLevel>(1));
        ClientManager = std::make_unique<td::ClientManager>();
        ClientID = ClientManager->create_client_id();
        SendQuery(td_api::make_object<td_api::getOption>("version"), {});
    }


    [[noreturn]] void run()
    {
        while(true)
        {
            if(bIsRestartRequired)
            {
                restart();
            }
            else if(!bIsAuthorized)
            {
                ProcessResponse(ClientManager->receive(TimeOut));
            }
            else
            {
                // Chat processor should be placed here.
            }
        }
    }


private:
    using TdObject = td_api::object_ptr<td_api::Object>;

    // ClientManager instance should be transfered to other
    // threads as well.
    std::unique_ptr<td::ClientManager> ClientManager;

    // This type of initialization guarantee that value will be
    // preinit with 0.
    std::int32_t ClientID{0};

    // Basic Authorization class.
    td_api::object_ptr<td_api::AuthorizationState> AuthtorizationState;


    // App states.
    // Shows whether user is authorized.
    bool bIsAuthorized{false};

    // Shows whether app requires to restart.
    bool bIsRestartRequired{false};


    // Queries.
    std::uint64_t CurrentQueryID{0};
    std::uint64_t AuthQueryID{0};


    // Fast-Access data.
    //
    std::map<std::uint64_t, std::function<void(TdObject)>> handlers;

    //
    std::map<std::int64_t, td_api::object_ptr<td_api::user>> users;

    //
    std::map<std::int64_t, std::string> ChatTitle;


    // Return next query ID.
    [[nodiscard]] std::uint64_t NextQueryID()
    {
        return ++CurrentQueryID;
    }


    // Get user name by the user ID.
    [[nodiscard]] std::string GetUserName(std::int64_t UserID) const
    {
        auto it = users.find(UserID);
        if(it == users.end())
        {
            return "Unknown user";
        }
        return it->second->first_name_ + " " + it->second->last_name_;
    }


    // Get chat title by chat ID.
    [[nodiscard]] std::string GetChatTitle(std::int64_t ChatID) const
    {
        auto it = ChatTitle.find(ChatID);
        if(it == ChatTitle.end())
        {
            return "Unknown chat";
        }
        return it->second;
    }


    // Create query handler.
    auto CreateAuthQueryHandler()
    {
        return [this, id = AuthQueryID](TdObject object)
        {
            if(id == AuthQueryID)
            {
                CheckAuthError(std::move(object));
            }
        };
    }


    // Restart current tcli instance. Not the whole app.
    [[noreturn]] void restart()
    {
        ClientManager.reset();
        *this = tcli();
    }


    // Send message to the query.
    [[noreturn]] void SendQuery(td_api::object_ptr<td_api::Function> func, std::function<void(TdObject)> handler)
    {
        auto QueryID = NextQueryID();
        if(handler)
        {
            handlers.emplace(QueryID, std::move(handler));
        }

        ClientManager->send(ClientID, QueryID, std::move(func));
    }


    // Processing response.
    [[noreturn]] void ProcessResponse(td::ClientManager::Response response)
    {
        if(!response.object)
        {
            return;
        }

        if(response.request_id == 0)
        {
            return ProcessUpdate(std::move(response.object));
        }

        auto it = handlers.find(response.request_id);
        if(it != handlers.end())
        {
            it->second(std::move(response.object));
            handlers.erase(it);
        }
    }


    // Process updates.
    [[noreturn]] void ProcessUpdate(TdObject update) // td_api::object_ptr<td_api::Object>
    {
        td_api::downcast_call(
        *update, overloaded(
                    [this](td_api::updateAuthorizationState &update_authorization_state) {
                        AuthtorizationState = std::move(update_authorization_state.authorization_state_);
                        OnAuthStateUpdate();
                    },
                    [this](td_api::updateNewChat &update_new_chat) {
                        ChatTitle[update_new_chat.chat_->id_] = update_new_chat.chat_->title_;
                    },
                    [this](td_api::updateChatTitle &update_chat_title) {
                        ChatTitle[update_chat_title.chat_id_] = update_chat_title.title_;
                    },
                    [this](td_api::updateUser &update_user) {
                        auto user_id = update_user.user_->id_;
                        users[user_id] = std::move(update_user.user_);
                    },
                    [this](td_api::updateNewMessage &update_new_message) {
                        auto chat_id = update_new_message.message_->chat_id_;
                        std::string sender_name;
                        td_api::downcast_call(*update_new_message.message_->sender_id_, overloaded(
                                                [this, &sender_name](td_api::messageSenderUser &user) {
                                                    sender_name = GetUserName(user.user_id_);
                                                },
                                                [this, &sender_name](td_api::messageSenderChat &chat) {
                                                    sender_name = GetChatTitle(chat.chat_id_);
                                                }));
                    std::string text;
                    if (update_new_message.message_->content_->get_id() == td_api::messageText::ID) {
                        text = static_cast<td_api::messageText &>(*update_new_message.message_->content_).text_->text_;
                    }
                    std::cout << "Receive message: [chat_id:" << chat_id << "] [from:" << sender_name << "] ["
                                << text << "]" << std::endl;
                    },
                    [](auto &update) {}));
    }


    // Authorization states.
    [[noreturn]] void OnAuthStateUpdate()
    {
        ++AuthQueryID;
        td_api::downcast_call(*AuthtorizationState, overloaded(
                                [this](td_api::authorizationStateReady &) {
                                    bIsAuthorized = true;
                                    std::cout << "Authorization is completed" << std::endl;
                                },
                                [this](td_api::authorizationStateLoggingOut &) {
                                    bIsAuthorized = false;
                                    std::cout << "Logging out" << std::endl;
                                },
                                [this](td_api::authorizationStateClosing &) { std::cout << "Closing" << std::endl; },
                                [this](td_api::authorizationStateClosed &) {
                                    bIsAuthorized = false;
                                    bIsRestartRequired = true;
                                    std::cout << "Terminated" << std::endl;
                                },
                                [this](td_api::authorizationStateWaitPhoneNumber &) {
                                    std::cout << "Enter phone number: " << std::flush;
                                    std::string phone_number;
                                    std::cin >> phone_number;
                                    SendQuery(
                                        td_api::make_object<td_api::setAuthenticationPhoneNumber>(phone_number, nullptr),
                                        CreateAuthQueryHandler());
                                },
                                [this](td_api::authorizationStateWaitPremiumPurchase &) {
                                    std::cout << "Telegram Premium subscription is required" << std::endl;
                                },
                                [this](td_api::authorizationStateWaitEmailAddress &) {
                                    std::cout << "Enter email address: " << std::flush;
                                    std::string email_address;
                                    std::cin >> email_address;
                                    SendQuery(td_api::make_object<td_api::setAuthenticationEmailAddress>(email_address),
                                                CreateAuthQueryHandler());
                                },
                                [this](td_api::authorizationStateWaitEmailCode &) {
                                    std::cout << "Enter email authentication code: " << std::flush;
                                    std::string code;
                                    std::cin >> code;
                                    SendQuery(td_api::make_object<td_api::checkAuthenticationEmailCode>(
                                                td_api::make_object<td_api::emailAddressAuthenticationCode>(code)),
                                                CreateAuthQueryHandler());
                                },
                                [this](td_api::authorizationStateWaitCode &) {
                                    std::cout << "Enter authentication code: " << std::flush;
                                    std::string code;
                                    std::cin >> code;
                                    SendQuery(td_api::make_object<td_api::checkAuthenticationCode>(code),
                                                CreateAuthQueryHandler());
                                },
                                [this](td_api::authorizationStateWaitRegistration &) {
                                    std::string first_name;
                                    std::string last_name;
                                    std::cout << "Enter your first name: " << std::flush;
                                    std::cin >> first_name;
                                    std::cout << "Enter your last name: " << std::flush;
                                    std::cin >> last_name;
                                    SendQuery(td_api::make_object<td_api::registerUser>(first_name, last_name, false),
                                                CreateAuthQueryHandler());
                                },
                                [this](td_api::authorizationStateWaitPassword &) {
                                    std::cout << "Enter authentication password: " << std::flush;
                                    std::string password;
                                    std::getline(std::cin, password);
                                    SendQuery(td_api::make_object<td_api::checkAuthenticationPassword>(password),
                                                CreateAuthQueryHandler());
                                },
                                [this](td_api::authorizationStateWaitOtherDeviceConfirmation &state) {
                                    std::cout << "Confirm this login link on another device: " << state.link_ << std::endl;
                                },
                                [this](td_api::authorizationStateWaitTdlibParameters &) {
                                    auto request = td_api::make_object<td_api::setTdlibParameters>();
                                    request->database_directory_ = DataDirectory;
                                    request->use_message_database_ = bUseCache;
                                    request->use_secret_chats_ = bSupportSecretChats;
                                    request->api_id_ = ApiID;
                                    request->api_hash_ = ApiHash;
                                    request->system_language_code_ = _locale;
                                    request->device_model_ = DeviceModel;
                                    request->application_version_ = VersionAsString;
                                    SendQuery(std::move(request), CreateAuthQueryHandler());
                                }));
    }


    // Check for authentication errors.
    [[noreturn]] void CheckAuthError(TdObject object)
    {
        if(object->get_id() == td_api::error::ID)
        {
            auto error = td::move_tl_object_as<td_api::error>(object);
            std::cout << "Error: " << td_api::to_string(error) << std::flush;
            OnAuthStateUpdate();
        }
    }
}; // class tcli.
