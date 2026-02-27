#pragma once



#include <iostream>
#include <string>
#include <regex>
#include <atomic>


#include "ftxui/dom/elements.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/screen/screen.hpp"





class AuthComponent
{
public:
    struct EmailParameters
    {
        std::string EmailAddress;
        std::string EmailAddressPattern;
        std::string EmailCode;
        std::atomic<bool> Process;
        std::atomic<bool> ValidationFailed;
        std::atomic<bool> ResetEmail;
        bool AllowEmailReset = false;
    };


    struct PhoneParameters
    {
        std::string PhoneNumber;
        std::string PhoneCode;
        std::atomic<bool> Process;
        std::atomic<bool> ValidationFailed;
        std::atomic<bool> ChangeNumber;
    };


    struct PasswordParameters
    {
        std::string Password;
        std::atomic<bool> Process;
        std::atomic<bool> ValidationFailed;
    };



    /**
     * Creates email-verification component.
     * 
     * @author Ilya Alexandrovich
     * 
     * @param Parameters  reference to an existing EmailParameters struct
     * 
     * @return email-verification component
     * 
     * @since 1.0.0
     */
    ftxui::Component CreateEmailAuthorizationComponent(EmailParameters& Parameters)
    {
        bool ValidationFailed = false;

        std::regex Regex{R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})"};

        std::string Status = "Telegram CLI";
        std::string InputPlaceHolder = "Enter your email here";
        std::string ValidationFailedText = "Incorrect email";
        std::string PlaceHolder = "Please enter email connected to this Telegram account";
        std::string InputContent;


        ftxui::Component StatusComponent = ftxui::Renderer([&]{
            return ftxui::text(Status);
        }) | ftxui::hcenter;


        ftxui::Component PlaceHolderComponent = ftxui::Renderer([&]{
            return ftxui::paragraphAlignCenter(PlaceHolder);
        });


        ftxui::Component ValidationFailedComponent = ftxui::Maybe(ftxui::Renderer([&]{
            return ftxui::text(ValidationFailedText);
        }), &ValidationFailed);


        ftxui::InputOption InputOptions = ftxui::InputOption::Spacious();
        InputOptions.content = InputContent;
        InputOptions.placeholder = InputPlaceHolder;
        InputOptions.transform = [&](ftxui::InputState State)
        {
            if(State.focused && !InputContent.empty())
            {
                ValidationFailed = false;
                return State.element = ftxui::text(InputContent);
            }
            else if(!InputContent.empty()) return State.element = ftxui::text(InputContent);
            return State.element = ftxui::text(InputPlaceHolder);
        };
        
        ftxui::Component InputComponent = ftxui::Input(InputOptions);


        ftxui::Component ConfirmButtonComponent = ftxui::Button("Confirm", [&]{
            if(!std::regex_match(InputContent, Regex)) ValidationFailed = true;
            else
            {
                Status = "Loading...";
                if(!Parameters.EmailAddress.empty()) Parameters.EmailAddress = InputContent;
                else Parameters.EmailCode = InputContent;


                Parameters.Process.store(true, std::memory_order_release);
                Parameters.Process.notify_one();


                Parameters.Process.wait(false);
                if(Parameters.ValidationFailed.load(std::memory_order_acquire))
                {
                    ValidationFailed = true;
                    InputComponent->TakeFocus();
                }
                else
                {
                    Status = "Telegram CLI";
                    InputPlaceHolder = "Enter your code here";
                    ValidationFailedText = "Incorrect code";
                    PlaceHolder = "Please enter the code sent to your email.";
                    Regex = std::regex{R"(.*)"};
                    InputComponent->TakeFocus();
                }
            }
        }, ftxui::ButtonOption::Animated());


        ftxui::Component ResetEmailButtonComponent = ftxui::Maybe(ftxui::Button("Reset email", [&]{
            Parameters.ResetEmail.store(true, std::memory_order_release);
        }, ftxui::ButtonOption::Animated()), &Parameters.AllowEmailReset);


        ftxui::Component EmailComponent = ftxui::Container::Vertical({
            PlaceHolderComponent,
            ValidationFailedComponent | ftxui::borderEmpty,
            InputComponent | ftxui::border | ftxui::hcenter,
            ConfirmButtonComponent | ftxui::borderEmpty | ftxui::hcenter,
        }) | ftxui::border | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 32) | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 15);


        ftxui::Component MainContent = ftxui::Container::Vertical({
            StatusComponent,
            EmailComponent,
            ResetEmailButtonComponent | ftxui::hcenter
        }) | ftxui::center;


        return MainContent;
    }



    /**
     * Creates phone=verification component.
     * 
     * @author Ilya Alexandrovich
     * 
     * @param Parameters  reference to an existing PhoneParameters struct
     * 
     * @return phone-verification component
     * 
     * @since 1.0.0
     */
    ftxui::Component CreatePhoneAuthorizationComponent(PhoneParameters& Parameters)
    {
        bool ValidationFailed = false;
        bool AllowChangeNumber = false;

        std::regex Regex{R"(/^\+\d{1,3}\d{4,14}$/)"};

        std::string Status = "Telegram CLI";
        std::string InputPlaceHolder = "Enter your phone number here";
        std::string ValidationFailedText = "Incorrect phone number";
        std::string PlaceHolder = "Please enter phone number connected to this Telegram account";
        std::string InputContent;


        ftxui::Component StatusComponent = ftxui::Renderer([&]{
            return ftxui::text(Status);
        }) | ftxui::hcenter;


        ftxui::Component PlaceHolderComponent = ftxui::Renderer([&]{
            return ftxui::paragraphAlignCenter(PlaceHolder);
        });


        ftxui::Component ValidationFailedComponent = ftxui::Maybe(ftxui::Renderer([&]{
            return ftxui::text(ValidationFailedText);
        }), &ValidationFailed);


        ftxui::InputOption InputOptions = ftxui::InputOption::Spacious();
        InputOptions.content = InputContent;
        InputOptions.placeholder = InputPlaceHolder;
        InputOptions.transform = [&](ftxui::InputState State)
        {
            if(State.focused && !InputContent.empty())
            {
                ValidationFailed = false;
                return State.element = ftxui::text(InputContent);
            }
            else if(!InputContent.empty()) return State.element = ftxui::text(InputContent);
            return State.element = ftxui::text(InputPlaceHolder);
        };
        
        ftxui::Component InputComponent = ftxui::Input(InputOptions);


        ftxui::Component ConfirmButtonComponent = ftxui::Button("Confirm", [&]{
            if(!std::regex_match(InputContent, Regex)) ValidationFailed = true;
            else
            {
                Status = "Loading...";
                if(!Parameters.PhoneNumber.empty()) Parameters.PhoneNumber = InputContent;
                else Parameters.PhoneCode = InputContent;


                Parameters.Process.store(true, std::memory_order_release);
                Parameters.Process.notify_one();


                Parameters.Process.wait(false);
                if(Parameters.ValidationFailed.load(std::memory_order_acquire))
                {
                    ValidationFailed = true;
                    InputComponent->TakeFocus();
                }
                else
                {
                    Status = "Telegram CLI";
                    InputPlaceHolder = "Enter your code here";
                    ValidationFailedText = "Incorrect code";
                    PlaceHolder = "Please enter the code sent to your phone.";
                    Regex = std::regex{R"(.*)"};
                    AllowChangeNumber = true;
                    InputComponent->TakeFocus();
                }
            }
        }, ftxui::ButtonOption::Animated());


        ftxui::Component ChangeNumberButtonComponent = ftxui::Maybe(ftxui::Button("Change phone number", [&]{
            Parameters.ChangeNumber.store(true, std::memory_order_release);
        }, ftxui::ButtonOption::Animated()), &AllowChangeNumber);


        ftxui::Component PhoneComponent = ftxui::Container::Vertical({
            PlaceHolderComponent,
            ValidationFailedComponent | ftxui::borderEmpty,
            InputComponent | ftxui::border | ftxui::hcenter,
            ConfirmButtonComponent | ftxui::borderEmpty | ftxui::hcenter,
        }) | ftxui::border | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 32) | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 15);


        ftxui::Component MainContent = ftxui::Container::Vertical({
            StatusComponent,
            PhoneComponent,
            ChangeNumberButtonComponent | ftxui::hcenter
        }) | ftxui::center;


        return MainContent;
    }
    


    /**
     * Creates password-verification component.
     * 
     * @author Ilya Alexandrovich
     * 
     * @param Parameters  reference to an existing PasswordParameters struct
     * 
     * @return return password-verification component
     * 
     * @since 1.0.0
     */
    ftxui::Component CreatePasswordAuthComponent(PasswordParameters& Parameters)
    {
        bool bIsValidationFailed = true;

        std::string Status = "Telegram CLI";
        std::string InputPlaceHolder = "Enter your password here";
        std::string ValidationFailedText = "Incorrect password";


        ftxui::Component StatusBar = ftxui::Renderer([&]
            {
                return ftxui::text(Status) | ftxui::hcenter;
            }
        );


        ftxui::Component PlaceHolderComponent = ftxui::Renderer([&]{
            return ftxui::paragraphAlignCenter("Please enter your cloud password");
        });

        
        ftxui::Component ValidationFailedComponent = ftxui::Maybe(ftxui::Renderer([&]
            {
                return ftxui::text(ValidationFailedText) | ftxui::hcenter;
            }), &bIsValidationFailed
        );


        ftxui::InputOption InputOptions = ftxui::InputOption::Spacious();
        InputOptions.content = Parameters.Password;
        InputOptions.placeholder = InputPlaceHolder;
        InputOptions.transform = [&](ftxui::InputState State){
            if(State.focused && !Parameters.Password.empty())
            {
                bIsValidationFailed = false;
                return State.element = ftxui::text(Parameters.Password);
            }
            else if(!Parameters.Password.empty()) return State.element = ftxui::text(Parameters.Password);
            return State.element = ftxui::text(InputPlaceHolder);
        };
        ftxui::Component InputComponent = ftxui::Input(InputOptions);


        ftxui::Component ConfirmButtonComponent = ftxui::Button("Confirm", [&]{
            if(Parameters.Password.length() < MinPasswordLength)
            {
                ValidationFailedText = "Password is too small";
                bIsValidationFailed = true;
            }
            else
            {
                Status = "Loading...";
                Parameters.Process.store(true, std::memory_order_release);
                Parameters.Process.notify_one();
                if(Parameters.ValidationFailed.load(std::memory_order_acquire))
                {
                    Status = "Telegram CLI";
                    ValidationFailedText = "Incorrect password";
                    bIsValidationFailed = true;
                    InputComponent->TakeFocus();
                }

            }
        }, ftxui::ButtonOption::Animated());


        ftxui::Component PasswordBox = ftxui::Container::Vertical({
            PlaceHolderComponent,
            ValidationFailedComponent | ftxui::borderEmpty,
            InputComponent | ftxui::border | ftxui::hcenter,
            ConfirmButtonComponent | ftxui::borderEmpty | ftxui::hcenter,
        }) | ftxui::border | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 32) | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 15);


        ftxui::Component MainContent = ftxui::Container::Vertical({
            StatusBar,
            PasswordBox,
        }) | ftxui::center;


        return MainContent;
    }



    /**
     * Creates waiting-for-premium component.
     * 
     * @author Ilya Alexandrovich
     * 
     * @return return waiting-for-premium component
     */
    ftxui::Component CreatePremiumRequiredAuthComponent()
    {
        std::string Status = "Loading...";
        ftxui::Component StatusBar = ftxui::Renderer([&]
            {
                return ftxui::text(Status) | ftxui::hcenter;
            }
        );


        ftxui::Component PremiumPlaceHolderComponent = ftxui::Renderer([&]{
            return ftxui::paragraphAlignCenter("Waiting for Premium");
        });


        ftxui::Component PremiumBox = ftxui::Container::Vertical(
        {
            PremiumPlaceHolderComponent
        }) | ftxui::border | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 32) | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 15);


        ftxui::Component MainContent = ftxui::Container::Vertical(
        {
            StatusBar,
            PremiumBox
        }) | ftxui::center | ftxui::focus;
        

        return MainContent;
    }


private:
    int const MinPasswordLength{8};
};


// !TODO: Add QR-Codes support.
// !TODO: Add additional confirmation for enter-email and enter-number forms.
