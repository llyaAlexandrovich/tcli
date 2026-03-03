#pragma once



#include <iostream>


#include "td/telegram/Client.h"
#include "td/telegram/td_api.h"
#include "td/telegram/td_api.hpp"


#include "types.hpp"
#include "tdhelper/tdtypes.hpp"




class TelegramAuthUpdates
{
public:
    TdAuthorizationState AuthorizationState;

    TelegramAuthUpdates();


    void CheckAuthError(TdObject object)
    {
        if(object->get_id() == td_api::error::ID)
        {
            auto error = td::move_tl_object_as<td_api::error>(object);
            std::cout << "Error: " << td_api::to_string(error) << std::flush;
            OnAuthStateUpdate();
        }
    }


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


    // See descriptions for this funtions elsewhere.
    virtual void AuthorizationComplete();
    virtual void AuthorizationLoggingOut();
    virtual void AuthorizationClosing();
    virtual void AuthorizationClosed();
    virtual void AuthorizationRequirePhoneNumber();
    virtual void AuthorizationPremiumRequired();
    virtual void AuthorizationRequireEmailAddress();
    virtual void AuthorizationRequireEmailCode();
    virtual void AuthorizationRequireAuthCode();
    virtual void AuthorizationRequireRegistration();
    virtual void AuthorizationRequireAuthPassword();
    virtual void AuthorizationRequireAnotherDeviceConfirmation();
    virtual void AuthorizationSetTdLibParameters();


    /**
     * Auth update mechanism.
     * 
     * @author Ilya Alexandrovich
     * 
     * @since 1.0.0
     */
    void OnAuthStateUpdate()
    {
        ++AuthQueryID;
        td_api::downcast_call(*AuthorizationState, overloaded(
                                [this](td_api::authorizationStateReady &)
                                {
                                    AuthorizationComplete();
                                },
                                [this](td_api::authorizationStateLoggingOut &)
                                {
                                    AuthorizationLoggingOut();
                                },
                                [this](td_api::authorizationStateClosing &)
                                {
                                    AuthorizationClosing();
                                },
                                [this](td_api::authorizationStateClosed &)
                                {
                                    AuthorizationClosed();
                                },
                                [this](td_api::authorizationStateWaitPhoneNumber &)
                                {
                                    AuthorizationRequirePhoneNumber();
                                },
                                [this](td_api::authorizationStateWaitPremiumPurchase &)
                                {
                                    AuthorizationPremiumRequired();
                                },
                                [this](td_api::authorizationStateWaitEmailAddress &)
                                {
                                    AuthorizationRequireEmailAddress();
                                },
                                [this](td_api::authorizationStateWaitEmailCode &)
                                {
                                    AuthorizationRequireEmailCode();
                                },
                                [this](td_api::authorizationStateWaitCode &)
                                {
                                    AuthorizationRequireAuthCode();
                                },
                                [this](td_api::authorizationStateWaitRegistration &)
                                {
                                    AuthorizationRequireRegistration();
                                },
                                [this](td_api::authorizationStateWaitPassword &)
                                {
                                    AuthorizationRequireAuthPassword();
                                },
                                [this](td_api::authorizationStateWaitOtherDeviceConfirmation &state)
                                {
                                    AuthorizationRequireAnotherDeviceConfirmation();
                                },
                                [this](td_api::authorizationStateWaitTdlibParameters &)
                                {
                                    AuthorizationSetTdLibParameters();
                                }));
    }


    void CheckAuthenticationError(TdObject Object)
    {
        if(Object->get_id() == td_api::error::ID)
        {
            auto error = td::move_tl_object_as<td_api::error>(Object);
            //std::cout << "Error " << to_string(error) << std::flush;
            OnAuthStateUpdate();
        }
    }


    auto CreateAuthenticationQueryHandler()
    {
        return [this, id = AuthQueryID](TdObject Object)
        {
            if(id == AuthQueryID)
            {
                CheckAuthenticationError(std::move(Object));
            }
        };
    }

    
    std::uint64_t AuthQueryID{0};

private:

};
