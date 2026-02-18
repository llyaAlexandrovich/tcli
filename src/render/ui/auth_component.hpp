#pragma once



#include <iostream>
#include <string>
#include <regex>


#include "td/telegram/Client.h"
#include "td/telegram/td_api.h"
#include "td/telegram/td_api.hpp"


#include "ftxui/dom/elements.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/screen/screen.hpp"


#include "tdhelper/tdtypes.hpp"



class AuthComponent
{
public:
    /**
     * Returns 'enter email' component.
     * 
     * @author Ilya Alexandrovich
     * 
     * @param InputContent  variable to store the email address
     * 
     * @return return ready to use in Loop() call ftxui::Component
     * 
     * @since 1.0.0
     */
    ftxui::Component CreateEmailAuthComponent(std::string& InputContent)
    {
        // Status component.
        std::string Status = "Telegram CLI";
        ftxui::Component StatusBar = ftxui::Renderer([&]
            {
                return ftxui::text(Status) | ftxui::hcenter;
            }
        );


        // PlaceHolder component.
        ftxui::Component PlaceHolderComponent = ftxui::Renderer([&]{
            return ftxui::paragraphAlignCenter(EmailAuthPlaceHolder);
        });


        // Validation failed component.
        bool bIsValidationFailed = false;
        ftxui::Component ValidationFailedText = ftxui::Maybe(ftxui::Renderer([&]
            {
                return ftxui::text(EmailAuthValidationFailedPlaceHolder) | ftxui::hcenter;
            }), &bIsValidationFailed
        );


        // Input component.
        ftxui::InputOption InputOptions = ftxui::InputOption::Spacious();
        InputOptions.content = InputContent;
        InputOptions.placeholder = EmailAuthInputPlaceHolder;
        InputOptions.transform = [&](ftxui::InputState State){
            if(State.focused && !InputContent.empty())
            {
                bIsValidationFailed = false;
                return State.element = ftxui::text(InputContent);
            }
            else if(!InputContent.empty()) return State.element = ftxui::text(InputContent);
            return State.element = ftxui::text(EmailAuthInputPlaceHolder);
        };
        ftxui::Component Input = ftxui::Input(InputOptions);


        // Confirm button component.
        ftxui::Component ConfirmButton = ftxui::Button(AuthConfigButtonPlaceHolder, [&]{
            if(!std::regex_match(InputContent, EmailRegex)) bIsValidationFailed = true;
            else Status = "Loading...";
        }, ftxui::ButtonOption::Animated());


        // Maternity.
        ftxui::Component EmailBox = ftxui::Container::Vertical({
            PlaceHolderComponent,
            ValidationFailedText | ftxui::borderEmpty,
            Input | ftxui::border | ftxui::hcenter,
            ConfirmButton | ftxui::borderEmpty | ftxui::hcenter,
        }) | ftxui::border | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 32) | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 15);


        ftxui::Component MainContent = ftxui::Container::Vertical({
            StatusBar,
            EmailBox,
        }) | ftxui::center;


        return MainContent;
    }



    /**
     * Returns 'enter phone number' component.
     * 
     * @author Ilya Alexandrovich
     * 
     * @param InputContent  variable to store the email address
     * 
     * @return return ready to use in Loop() call ftxui::Component
     * 
     * @since 1.0.0
     */
    ftxui::Component CreatePhoneAuthComponent(std::string& InputContent)
    {
        // Status component.
        std::string Status = "Telegram CLI";
        ftxui::Component StatusBar = ftxui::Renderer([&]
            {
                return ftxui::text(Status) | ftxui::hcenter;
            }
        );


        // PlaceHolder component.
        ftxui::Component PlaceHolderComponent = ftxui::Renderer([&]{
            return ftxui::paragraphAlignCenter(PhoneAuthPlaceHolder);
        });


        // Validation failed component.
        bool bIsValidationFailed = false;
        ftxui::Component ValidationFailedText = ftxui::Maybe(ftxui::Renderer([&]
            {
                return ftxui::text(PhoneAuthValidationFailedPlaceHolder) | ftxui::hcenter;
            }), &bIsValidationFailed
        );


        // Input component.
        ftxui::InputOption InputOptions = ftxui::InputOption::Spacious();
        InputOptions.content = InputContent;
        InputOptions.placeholder = PhoneAuthInputPlaceHolder;
        InputOptions.transform = [&](ftxui::InputState State){
            if(State.focused && !InputContent.empty())
            {
                bIsValidationFailed = false;
                return State.element = ftxui::text(InputContent);
            }
            else if(!InputContent.empty()) return State.element = ftxui::text(InputContent);
            return State.element = ftxui::text(PhoneAuthInputPlaceHolder);
        };
        ftxui::Component Input = ftxui::Input(InputOptions);


        // Confirm button component.
        ftxui::Component ConfirmButton = ftxui::Button(AuthConfigButtonPlaceHolder, [&]{
            if(!std::regex_match(InputContent, PhoneRegex)) bIsValidationFailed = true;
            else Status = "Loading...";
        }, ftxui::ButtonOption::Animated());


        // Maternity.
        ftxui::Component EmailBox = ftxui::Container::Vertical({
            PlaceHolderComponent,
            ValidationFailedText | ftxui::borderEmpty,
            Input | ftxui::border | ftxui::hcenter,
            ConfirmButton | ftxui::borderEmpty | ftxui::hcenter,
        }) | ftxui::border | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 32) | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 15);


        ftxui::Component MainContent = ftxui::Container::Vertical({
            StatusBar,
            EmailBox,
        }) | ftxui::center;


        return MainContent;
    }



    /**
     * Returns 'enter code from email' component.
     * 
     * @author Ilya Alexandrovich
     * 
     * @param InputContent  variable to store the code
     * @param bIsEmailChangeRequired  indicates whether user request to change email
     * @param EmailContent  email itself
     * 
     * @return return 'enter code from email' ftxui::Component
     * 
     * @since 1.0.0
     */
    ftxui::Component CreateEmailAuthCodeComponent(std::string& InputContent, bool& bIsEmailChangeRequired, std::string EmailContent)
    {
        // Status component.
        std::string Status = "Telegram CLI";
        ftxui::Component StatusBar = ftxui::Renderer([&]
            {
                return ftxui::text(Status) | ftxui::hcenter;
            }
        );


        // PlaceHolder component.
        ftxui::Component PlaceHolderComponent = ftxui::Renderer([&]{
            return ftxui::paragraphAlignCenter(EmailAuthCodePlaceHolder + ": " + EmailContent);
        });


        // Validation failed component.
        bool bIsValidationFailed = false;
        ftxui::Component ValidationFailedText = ftxui::Maybe(ftxui::Renderer([&]
            {
                return ftxui::text(AuthCodeValidationFailedPlaceHolder) | ftxui::hcenter;
            }), &bIsValidationFailed
        );


        // First attempt failed component.
        bool bIsFirstAttemptfailed = false;
        ftxui::Component ChangeButton = ftxui::Maybe(ftxui::Button(AuthChangeNumberButtonPlaceHolder, [&]{
            bIsEmailChangeRequired = true;
            return;
        }, ftxui::ButtonOption::Animated()) | ftxui::hcenter, &bIsFirstAttemptfailed);


        // Input component.
        ftxui::InputOption InputOptions = ftxui::InputOption::Spacious();
        InputOptions.content = InputContent;
        InputOptions.placeholder = AuthCodeInputPlaceHolder;
        InputOptions.transform = [&](ftxui::InputState State){
            if(State.focused && !InputContent.empty())
            {
                bIsValidationFailed = false;
                return State.element = ftxui::text(InputContent);
            }
            else if(!InputContent.empty()) return State.element = ftxui::text(InputContent);
            return State.element = ftxui::text(AuthCodeInputPlaceHolder);
        };
        ftxui::Component Input = ftxui::Input(InputOptions);


        // Confirm button component.
        ftxui::Component ConfirmButton = ftxui::Button(AuthConfigButtonPlaceHolder, [&]{
            if(InputContent.length() != AuthCodeLength)
            {
                bIsValidationFailed = true;
                bIsFirstAttemptfailed = true;
            }
            else Status = "Loading...";
        }, ftxui::ButtonOption::Animated());


        // Maternity.
        ftxui::Component EmailBox = ftxui::Container::Vertical({
            PlaceHolderComponent,
            ValidationFailedText | ftxui::borderEmpty,
            Input | ftxui::border | ftxui::hcenter,
            ConfirmButton | ftxui::borderEmpty | ftxui::hcenter,
        }) | ftxui::border | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 32) | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 15);


        ftxui::Component MainContent = ftxui::Container::Vertical({
            StatusBar,
            EmailBox,
            ChangeButton
        }) | ftxui::center;


        return MainContent;
    }



    /**
     * Returns 'enter code from message' component.
     * 
     * @author Ilya Alexandrovich
     * 
     * @param InputContent  variable to store the code
     * @param bIsEmailChangeRequired  indicates whether user request to change email
     * @param PhoneContent  phone itself
     * 
     * @return return 'enter code from message' ftxui::Component
     * 
     * @since 1.0.0
     */
    ftxui::Component CreatePhoneAuthCodeComponent(std::string& InputContent, bool& bIsPhoneChangeRequired, std::string PhoneContent)
    {
        // Status component.
        std::string Status = "Telegram CLI";
        ftxui::Component StatusBar = ftxui::Renderer([&]
            {
                return ftxui::text(Status) | ftxui::hcenter;
            }
        );


        // PlaceHolder component.
        ftxui::Component PlaceHolderComponent = ftxui::Renderer([&]{
            return ftxui::paragraphAlignCenter(PhoneAuthCodePlaceHolder + ": " + PhoneContent);
        });


        // Validation failed component.
        bool bIsValidationFailed = false;
        ftxui::Component ValidationFailedText = ftxui::Maybe(ftxui::Renderer([&]
            {
                return ftxui::text(AuthChangeEmailButtonPlaceHolder) | ftxui::hcenter;
            }), &bIsValidationFailed
        );


        // First attempt failed component.
        bool bIsFirstAttemptfailed = false;
        ftxui::Component ChangeButton = ftxui::Maybe(ftxui::Button(AuthChangeNumberButtonPlaceHolder, [&]{
            bIsPhoneChangeRequired = true;
            return;
        }, ftxui::ButtonOption::Animated()) | ftxui::hcenter, &bIsFirstAttemptfailed);


        // Input component.
        ftxui::InputOption InputOptions = ftxui::InputOption::Spacious();
        InputOptions.content = InputContent;
        InputOptions.placeholder = AuthCodeInputPlaceHolder;
        InputOptions.transform = [&](ftxui::InputState State){
            if(State.focused && !InputContent.empty())
            {
                bIsValidationFailed = false;
                return State.element = ftxui::text(InputContent);
            }
            else if(!InputContent.empty()) return State.element = ftxui::text(InputContent);
            return State.element = ftxui::text(AuthCodeInputPlaceHolder);
        };
        ftxui::Component Input = ftxui::Input(InputOptions);


        // Confirm button component.
        ftxui::Component ConfirmButton = ftxui::Button(AuthConfigButtonPlaceHolder, [&]{
            if(InputContent.length() != AuthCodeLength)
            {
                bIsValidationFailed = true;
                bIsFirstAttemptfailed = true;
            }
            else Status = "Loading...";
        }, ftxui::ButtonOption::Animated());


        // Maternity.
        ftxui::Component EmailBox = ftxui::Container::Vertical({
            PlaceHolderComponent,
            ValidationFailedText | ftxui::borderEmpty,
            Input | ftxui::border | ftxui::hcenter,
            ConfirmButton | ftxui::borderEmpty | ftxui::hcenter,
        }) | ftxui::border | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 32) | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 15);


        ftxui::Component MainContent = ftxui::Container::Vertical({
            StatusBar,
            EmailBox,
            ChangeButton
        }) | ftxui::center;


        return MainContent;
    }
    


    /**
     * Returns 'email code invalid try againg' component
     * 
     * @author Ilya Alexandrovich
     * 
     * @param InputContent variable to store the code
     * @param bIsEmailChangeRequired  indicates whether user request to change email
     * @param EmailContent  email itself
     * 
     * @return return 'email code invalid try again' ftxui::Component
     * 
     * @since 1.0.0
     */
    ftxui::Component CreateEmailAuthCodeFailedComponent(std::string& InputContent, bool& bIsEmailChangeRequired, std::string EmailContent)
    {
        // Status component.
        std::string Status = "Telegram CLI";
        ftxui::Component StatusBar = ftxui::Renderer([&]
            {
                return ftxui::text(Status) | ftxui::hcenter;
            }
        );


        // PlaceHolder component.
        ftxui::Component PlaceHolderComponent = ftxui::Renderer([&]{
            return ftxui::paragraphAlignCenter(EmailAuthCodePlaceHolder + ": " + EmailContent);
        });


        // Validation failed component.
        bool bIsValidationFailed = true;
        ftxui::Component ValidationFailedText = ftxui::Maybe(ftxui::Renderer([&]
            {
                return ftxui::text(AuthCodeValidationFailedPlaceHolder) | ftxui::hcenter;
            }), &bIsValidationFailed
        );


        // First attempt failed component.
        bool bIsFirstAttemptfailed = false;
        ftxui::Component ChangeButton = ftxui::Maybe(ftxui::Button(AuthChangeNumberButtonPlaceHolder, [&]{
            bIsEmailChangeRequired = true;
            return;
        }, ftxui::ButtonOption::Animated()) | ftxui::hcenter, &bIsFirstAttemptfailed);


        // Input component.
        ftxui::InputOption InputOptions = ftxui::InputOption::Spacious();
        InputOptions.content = InputContent;
        InputOptions.placeholder = AuthCodeInputPlaceHolder;
        InputOptions.transform = [&](ftxui::InputState State){
            if(State.focused && !InputContent.empty())
            {
                bIsValidationFailed = false;
                return State.element = ftxui::text(InputContent);
            }
            else if(!InputContent.empty()) return State.element = ftxui::text(InputContent);
            return State.element = ftxui::text(AuthCodeInputPlaceHolder);
        };
        ftxui::Component Input = ftxui::Input(InputOptions);


        // Confirm button component.
        ftxui::Component ConfirmButton = ftxui::Button(AuthConfigButtonPlaceHolder, [&]{
            if(InputContent.length() != AuthCodeLength)
            {
                bIsValidationFailed = true;
                bIsFirstAttemptfailed = true;
            }
            else Status = "Loading...";
        }, ftxui::ButtonOption::Animated());


        // Maternity.
        ftxui::Component EmailBox = ftxui::Container::Vertical({
            PlaceHolderComponent,
            ValidationFailedText | ftxui::borderEmpty,
            Input | ftxui::border | ftxui::hcenter,
            ConfirmButton | ftxui::borderEmpty | ftxui::hcenter,
        }) | ftxui::border | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 32) | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 15);


        ftxui::Component MainContent = ftxui::Container::Vertical({
            StatusBar,
            EmailBox,
            ChangeButton
        }) | ftxui::center;


        return MainContent;
    }



    /**
     * Returns 'phone code invalid try againg' component
     * 
     * @author Ilya Alexandrovich
     * 
     * @param InputContent variable to store the code
     * @param bIsPhoneChangeRequired  indicates whether user request to change email
     * @param PhoneContent  email itself
     * 
     * @return return 'phone code invalid try again' ftxui::Component
     * 
     * @since 1.0.0
     */
    ftxui::Component CreateEmailAuthCodeFailedComponent(std::string& InputContent, bool& bIsPhoneChangeRequired, std::string PhoneContent)
    {
        // Status component.
        std::string Status = "Telegram CLI";
        ftxui::Component StatusBar = ftxui::Renderer([&]
            {
                return ftxui::text(Status) | ftxui::hcenter;
            }
        );


        // PlaceHolder component.
        ftxui::Component PlaceHolderComponent = ftxui::Renderer([&]{
            return ftxui::paragraphAlignCenter(PhoneAuthCodePlaceHolder + ": " + PhoneContent);
        });


        // Validation failed component.
        bool bIsValidationFailed = true;
        ftxui::Component ValidationFailedText = ftxui::Maybe(ftxui::Renderer([&]
            {
                return ftxui::text(AuthCodeValidationFailedPlaceHolder) | ftxui::hcenter;
            }), &bIsValidationFailed
        );


        // First attempt failed component.
        bool bIsFirstAttemptfailed = false;
        ftxui::Component ChangeButton = ftxui::Maybe(ftxui::Button(AuthChangeNumberButtonPlaceHolder, [&]{
            bIsPhoneChangeRequired = true;
            return;
        }, ftxui::ButtonOption::Animated()) | ftxui::hcenter, &bIsFirstAttemptfailed);


        // Input component.
        ftxui::InputOption InputOptions = ftxui::InputOption::Spacious();
        InputOptions.content = InputContent;
        InputOptions.placeholder = AuthCodeInputPlaceHolder;
        InputOptions.transform = [&](ftxui::InputState State){
            if(State.focused && !InputContent.empty())
            {
                bIsValidationFailed = false;
                return State.element = ftxui::text(InputContent);
            }
            else if(!InputContent.empty()) return State.element = ftxui::text(InputContent);
            return State.element = ftxui::text(AuthCodeInputPlaceHolder);
        };
        ftxui::Component Input = ftxui::Input(InputOptions);


        // Configrm button component.
        ftxui::Component ConfirmButton = ftxui::Button(AuthConfigButtonPlaceHolder, [&]{
            if(InputContent.length() != AuthCodeLength) bIsValidationFailed = true;
            else Status = "Loading...";
        }, ftxui::ButtonOption::Animated());


        // Maternity.
        ftxui::Component EmailBox = ftxui::Container::Vertical({
            PlaceHolderComponent,
            ValidationFailedText | ftxui::borderEmpty,
            Input | ftxui::border | ftxui::hcenter,
            ConfirmButton | ftxui::borderEmpty | ftxui::hcenter,
        }) | ftxui::border | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 32) | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 15);


        ftxui::Component MainContent = ftxui::Container::Vertical({
            StatusBar,
            EmailBox,
        }) | ftxui::center;


        return MainContent;
    }


private:
    // Placeholders.
    std::string EmailAuthPlaceHolder = "Please enter email connected to this Telegram account";
    std::string EmailAuthCodePlaceHolder = "Please enter the code sended to your email";
    std::string PhoneAuthPlaceHolder = "Please enter phone number connected to this Telegram account";
    std::string PhoneAuthCodePlaceHolder = "Please enter the code sended to your phone number";


    std::string EmailAuthInputPlaceHolder = "Enter your email here";
    std::string PhoneAuthInputPlaceHolder = "Enter your phone number here";
    std::string AuthCodeInputPlaceHolder = "Enter your code here";


    std::string EmailAuthValidationFailedPlaceHolder = "Incorrect email";
    std::string PhoneAuthValidationFailedPlaceHolder = "Incorrect phone number";
    std::string AuthCodeValidationFailedPlaceHolder = "Invalid code";


    std::string AuthChangeNumberButtonPlaceHolder = "Change number";
    std::string AuthChangeEmailButtonPlaceHolder = "Change email";
    std::string AuthConfigButtonPlaceHolder = "Confirm";


    std::regex EmailRegex{R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})"};
    std::regex PhoneRegex{R"(/^\+\d{1,3}\d{4,14}$/)"};


    int const AuthCodeLength{5};
};


/**
 * !NOTE Theoretically I only need to add registration through QR codes support. It'll be hard to do though.
 */
