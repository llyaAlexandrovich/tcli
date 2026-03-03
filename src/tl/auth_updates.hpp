#pragma once



#include <iostream>


#include "td/telegram/Client.h"
#include "td/telegram/td_api.h"
#include "td/telegram/td_api.hpp"


#include "types.hpp"
#include "tdhelper/tdtypes.hpp"





template <typename T>
class TelegramAuthUpdates
{
public:
    TelegramAuthUpdates() = default;


    initTelegramAuthUpdates()
    {
        TelegramCLI = static_cast<T*>(this);
    }



    
    void AuthorizationLoggingOut();
    void AuthorizationClosing();
    void AuthorizationClosed();
    void AuthorizationRequirePhoneNumber();
    void AuthorizationPremiumRequired();
    void AuthorizationRequireEmailAddress();
    void AuthorizationRequireEmailCode();
    void AuthorizationRequireAuthCode();
    void AuthorizationRequireRegistration();
    void AuthorizationRequireAuthPassword();
    void AuthorizationRequireAnotherDeviceConfirmation();
    void AuthorizationSetTdLibParameters();


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


private:
    T* TelegramCLI;
    
    TdAuthorizationState AuthorizationState;
    
    std::uint64_t AuthQueryID{0};



    // !WARN: Uselesss peace of crap.
    void CheckAuthenticationError(TdObject Object)
    {
        if(Object->get_id() == td_api::error::ID)
        {
            auto error = td::move_tl_object_as<td_api::error>(Object);
            //std::cout << "Error " << to_string(error) << std::flush;
            OnAuthStateUpdate();
        }
    }



    // !WARN: Uselesss peace of crap.
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



    // Authorization state is complete.
    void AuthorizationComplete()
    {
        bIsAuthorized = true;
    }



    // Logging out.
    void AuthorizationLoggingOut()
    {
        bIsAuthorized = false;
    }



    // Closing state.
    void AuthorizationClosing()
    {
       // !TODO: I will need to add closing scene.
    }



    // Close state.
    void AuthorizationClosed()
    {
        bIsAuthorized = false;
        bIsRestartRequired = true;
    }



    // Authorization through the phone number.
    void AuthorizationRequirePhoneNumber()
    {
        std::string PhoneNumber;
        atomic<bool> OnProcess = false;
        T->RenderPhoneAuthScene(PhoneNumber, OnProcess);
        OnProcess.wait(false);
        OnProcess.wait(false);
        T->SendQuery(
            td_api::make_object<td_api::setAuthenticationPhoneNumber>(PhoneNumber, nullptr),
            [&](TdObject Object)
            {

            }
        );
    }



    // Telegram Premium subscription is required to continue authorization.
    void AuthorizationPremiumRequired()
    {
        T->RenderPremiumRequiredAuthScene();
    }



    // Authorization through the email.
    void AuthorizationRequireEmailAddress()
    {
        std::string EmailAddress;
        atomic<bool> OnProcess = false;
        T->RenderEmailAuthScene(EmailAddress, OnProcess);
        OnProcess.wait(false);
        T->SendQuery(
            td_api::make_object<td_api::setAuthenticationEmailAddress>(EmailAddress),
            [&](TdObject Object)
            {
                
            }
        );
    }



    // Authorization requires code from the email.
    void AuthorizationRequireEmailCode()
    {
        using std::chrono_literals;
        std::string EmailCode;
        std::atomic<bool> OnProcess = false;
        std::atomic<bool> ValidationFailedActive = false;
        T->RenderEmailCodeAuthScene(EmailCode, OnProcess, ValidationFailedActive);
        OnProcess.wait(false);
        T->SendQuery(
            td_api::make_object<td_api::checkAuthenticationEmailCode>(
                td_api::make_object<td_api::emailAddressAuthenticationCode>(EmailCode)),
            [&](TdObject Object)
            {
                if(Object->get_id() != td_api::error::ID) return;
                auto error = td_api::move_object_as<TdErrorT>(Object);
                if(message == "EMAIL_CODE_INVALID")
                {
                    T->SendQuery(
                        td_api::make_object<td_api::resendAuthenticationCode>(td_api::make_object<td_api::resendCodeReasonVerificationFailed>),
                        [&](TdObject Object)
                        {
                            if(Object->get_id() != td_api::error::ID) return;
                            auto error = td_api::move_object_as<TdErrorT>(Object);

                            
                        }
                    );
                }
                else if(message == "EMAIL_CODE_EXPIRED")
                {

                }
                else if(message.find("FLOOD_WAIT_") == 0)
                {
                    std::string FloodMessage = error->message_;
                    FloodMessage.erase(0, 12);
                    RenderFloodWaitScene(error->message_, std::stoi(FloodMessage) * 1s);
                }
            }
        );
    }
};
