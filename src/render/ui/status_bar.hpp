#pragma once



#include <iostream>
#include <string>


#include "ftxui/dom/elements.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/screen/screen.hpp"






class StatusBar
{
public:
    StatusBar()
    {
        StatusBarComponent = ftxui::Renderer([&]{
            return ftxui::text(Status) | ftxui::hcenter;
        });
    }


    enum class StatusType : int
    {
        Active = 1,
        Loading
    };


    void UpdateStatus(StatusType Type)
    {
        switch(Type){
            case StatusType::Active:
                Status = StatusMainPlaceHolder;
                return;
            case StatusType::Loading:
                Status = StatusLoadingPlaceHolder;
                return;
        }
    } 

    ftxui::Component StatusBarComponent;

private:
    std::string Status;
    std::string StatusMainPlaceHolder = "Telegram CLI";
    std::string StatusLoadingPlaceHolder = "Loading...";
};
