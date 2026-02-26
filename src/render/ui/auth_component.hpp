#pragma once



#include <iostream>
#include <string>
#include <regex>
#include <atomic>


#include "ftxui/dom/elements.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/screen/screen.hpp"





/**
 * For those who would ask why is there so many similar funcitons ->
 * This file provides auth components and as long as different pages
 * of authorization might be called different I would prefer using 
 * different components for each and one of them.
 */
class AuthComponent
{
public:
    /**
     * Returns 'enter email' component.
     * 
     * @author Ilya Alexandrovich
     * 
     * @param InputContent  variable to store the email address
     * @param OnProcess  confirm button callback
     * 
     * @return return ready to use in Loop() call ftxui::Component
     * 
     * @since 1.0.0
     */
    ftxui::Component CreateEmailAuthComponent(std::string& InputContent, std::atomic<bool>& OnProcess)
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
        ftxui::Component ConfirmButton = ftxui::Button(ConfirmButtonPlaceHolder, [&]{
            if(!std::regex_match(InputContent, EmailRegex)) bIsValidationFailed = true;
            else
            {
                Status = "Loading...";
                OnProcess.store(true, std::memory_order_release);
                OnProcess.notify_one();
            }
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
     * @param OnProcess  confirm button callback
     * 
     * @return return ready to use in Loop() call ftxui::Component
     * 
     * @since 1.0.0
     */
    ftxui::Component CreatePhoneAuthComponent(std::string& InputContent, std::atomic<bool>& OnProcess)
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
        ftxui::Component ConfirmButton = ftxui::Button(ConfirmButtonPlaceHolder, [&]{
            if(!std::regex_match(InputContent, PhoneRegex)) bIsValidationFailed = true;
            else
            {
                Status = "Loading...";
                DetailsContent = InputContent;
                OnProcess.store(true, std::memory_order_release);
                OnProcess.notify_one();
            }
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
     * @param OnProcess  confirm button callback
     * @param EmailPlaceHolder  fancy email place holder
     * @param ValidationFailedActive  set for the validation failed check
     * 
     * @return return 'enter code from email' ftxui::Component
     * 
     * @since 1.0.0
     */
    ftxui::Component CreateEmailAuthCodeComponent(std::string& InputContent, std::atomic<bool>& OnProcess, std::string& EmailPlaceHolder, std::atomic<bool>& ValidationFailedActive)
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
            return ftxui::paragraphAlignCenter(EmailAuthCodePlaceHolder + ": " + EmailPlaceHolder);
        });


        // Validation failed component.
        bool bIsValidationFailed = ValidationFailedActive;
        ftxui::Component ValidationFailedText = ftxui::Maybe(ftxui::Renderer([&]
            {
                return ftxui::text(AuthCodeValidationFailedPlaceHolder) | ftxui::hcenter;
            }), &bIsValidationFailed
        );


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
        ftxui::Component ConfirmButton = ftxui::Button(ConfirmButtonPlaceHolder, [&]{
            if(InputContent.length() != AuthCodeLength)
            {
                bIsValidationFailed = true;
            }
            else
            {
                Status = "Loading...";
                OnProcess.store(true, std::memory_order_release);
                OnProcess.notify_one();
                while(true)
                {
                    if(ValidationFailedActive.load(std::memory_order_acquire))
                    {
                        bIsValidationFailed = true;
                        break;
                    }
                }
            }
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
            EmailBox            
        }) | ftxui::center;


        return MainContent;
    }



    /**
     * Returns 'enter code from message' component.
     * 
     * @author Ilya Alexandrovich
     * 
     * @param InputContent  variable to store the code
     * @param OnProcess  confirm button callback
     * @param OnDetailsChange  details change request callback
     * @param ValidationFailedActive  set for the validation failed check
     * 
     * @return return 'enter code from message' ftxui::Component
     * 
     * @since 1.0.0
     */
    ftxui::Component CreatePhoneAuthCodeComponent(std::string& InputContent, std::atomic<bool>& OnProcess, std::atomic<bool>& OnDetailsChange, std::atomic<bool>& ValidationFailedActive)
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
            return ftxui::paragraphAlignCenter(PhoneAuthCodePlaceHolder + ": " + DetailsContent);
        });


        // Validation failed component.
        bool bIsValidationFailed = false;
        ftxui::Component ValidationFailedText = ftxui::Maybe(ftxui::Renderer([&]
            {
                return ftxui::text(AuthChangeEmailButtonPlaceHolder) | ftxui::hcenter;
            }), &bIsValidationFailed
        );


        // Change details component.
        bool bIsFirstAttemptfailed = false;
        ftxui::Component ChangeButton = ftxui::Maybe(ftxui::Button(AuthChangeNumberButtonPlaceHolder, [&]{
            OnDetailsChange.store(true, std::memory_order_release);
            OnProcess.store(true, std::memory_order_release);
            OnProcess.notify_one();
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
        ftxui::Component ConfirmButton = ftxui::Button(ConfirmButtonPlaceHolder, [&]{
            if(InputContent.length() != AuthCodeLength)
            {
                bIsValidationFailed = true;
                bIsFirstAttemptfailed = true;
            }
            else
            {
                Status = "Loading...";
                OnProcess.store(true, std::memory_order_release);
                OnProcess.notify_one();
                while(true)
                {
                    if(ValidationFailedActive.load(std::memory_order_acquire))
                    {
                        bIsValidationFailed = true;
                        break;
                    }
                }
            }
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
     * Returns 'enter password' component
     * 
     * @author Ilya Alexandrovich
     * 
     * @param InputContent  variable to store the password
     * @param OnProcess  confirm button callback
     * @param ValidationFailedActive  set for the validation failed check
     * 
     * @return return 'enter your password' component
     * 
     * @since 1.0.0
     */
    ftxui::Component CreatePasswordAuthComponent(std::string& InputContent, std::atomic<bool>& OnProcess, std::atomic<bool>& ValidationFailedActive)
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
            return ftxui::paragraphAlignCenter(PasswordAuthPlaceHolder);
        });


        // Validation failed component.
        bool bIsValidationFailed = true;
        std::string ValidationInvalidReason = PasswordAuthValidationFailedPlaceHolder;
        ftxui::Component ValidationFailedText = ftxui::Maybe(ftxui::Renderer([&]
            {
                return ftxui::text(ValidationInvalidReason) | ftxui::hcenter;
            }), &bIsValidationFailed
        );


        // Input component.
        ftxui::InputOption InputOptions = ftxui::InputOption::Spacious();
        InputOptions.content = InputContent;
        InputOptions.placeholder = PasswordAuthInputPlaceHolder;
        InputOptions.transform = [&](ftxui::InputState State){
            if(State.focused && !InputContent.empty())
            {
                bIsValidationFailed = false;
                InputOptions.placeholder = PasswordAuthInputPlaceHolder;
                return State.element = ftxui::text(InputContent);
            }
            else if(!InputContent.empty()) return State.element = ftxui::text(InputContent);
            return State.element = ftxui::text(PasswordAuthInputPlaceHolder);
        };
        ftxui::Component Input = ftxui::Input(InputOptions);


        // Configrm button component.
        ftxui::Component ConfirmButton = ftxui::Button(ConfirmButtonPlaceHolder, [&]{
            if(InputContent.length() < MinPasswordLength)
            {
                ValidationInvalidReason = PasswordIsTooSmallPlaceHolder;
                bIsValidationFailed = true;
            }
            else
            {
                Status = "Loading...";
                OnProcess.store(true, std::memory_order_release);
                OnProcess.notify_one();
                while(true)
                {
                    if(ValidationFailedActive.load(std::memory_order_acquire))
                    {
                        ValidationInvalidReason = PasswordAuthValidationFailedPlaceHolder;
                        bIsValidationFailed = true;
                        break;
                    }
                }
            }
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
     * Returns 'wait for premium' component.
     * 
     * @author Ilya Alexandrovich
     * 
     * @return return 'waiting for premium' component
     */
    ftxui::Component CreatePremiumRequiredAuthComponent()
    {
        // Status component.
        std::string Status = "Loading...";
        ftxui::Component StatusBar = ftxui::Renderer([&]
            {
                return ftxui::text(Status) | ftxui::hcenter;
            }
        );

        // PlaceHolder component.
        ftxui::Component PlaceHolderComponent = ftxui::Renderer([&]{
            return ftxui::paragraphAlignCenter(PremiumRequiredAuthPlaceHolder);
        });


        ftxui::Component Premium = ftxui::Renderer([&]
        {
            return ftxui::vbox(
                {
                    ftxui::text(PremiumRequiredAuthPlaceHolder) | ftxui::borderEmpty | ftxui::center,
                }) | ftxui::border;
        });


        // Maternity.
        ftxui::Component PremiumBox = ftxui::Container::Vertical(
        {
            PlaceHolderComponent,
            Premium
        }) | ftxui::border | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 32) | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 15);


        ftxui::Component MainContent = ftxui::Container::Vertical(
        {
            StatusBar,
            PremiumBox
        }) | ftxui::center | ftxui::focus;
        
        return MainContent;
    }


private:
    // Placeholders.
    std::string EmailAuthPlaceHolder = "Please enter email connected to this Telegram account";
    std::string EmailAuthCodePlaceHolder = "Please enter the code sended to your email";
    std::string PhoneAuthPlaceHolder = "Please enter phone number connected to this Telegram account";
    std::string PhoneAuthCodePlaceHolder = "Please enter the code sended to your phone number";
    std::string PasswordAuthPlaceHolder = "Please enter your cloud password";
    std::string PremiumRequiredAuthPlaceHolder = "Waiting for Premium";


    std::string EmailAuthInputPlaceHolder = "Enter your email here";
    std::string PhoneAuthInputPlaceHolder = "Enter your phone number here";
    std::string AuthCodeInputPlaceHolder = "Enter your code here";
    std::string PasswordAuthInputPlaceHolder = "Enter your password here";


    std::string EmailAuthValidationFailedPlaceHolder = "Incorrect email";
    std::string PhoneAuthValidationFailedPlaceHolder = "Incorrect phone number";
    std::string AuthCodeValidationFailedPlaceHolder = "Invalid code";
    std::string PasswordAuthValidationFailedPlaceHolder = "Incorrect password";
    std::string PasswordIsTooSmallPlaceHolder = "Password is too small";


    std::string AuthChangeNumberButtonPlaceHolder = "Change number";
    std::string AuthChangeEmailButtonPlaceHolder = "Change email";
    std::string ConfirmButtonPlaceHolder = "Confirm";


    std::regex EmailRegex{R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})"};
    std::regex PhoneRegex{R"(/^\+\d{1,3}\d{4,14}$/)"};


    int const AuthCodeLength{5};
    int const MinPasswordLength{8};


    // Whether phone or email itself.
    std::string DetailsContent;
};


/**
 * !NOTE Theoretically I only need to add registration through QR codes support. It'll be hard to do though. I forget password.
 * !WARN: I need to add another confirmation form for phone and email inputs.
 */