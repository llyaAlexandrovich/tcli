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
        StatusBar = ftxui::Renderer([&]{
            return ftxui::text(Status) | ftxui::hcenter;
        });
    }


    void UpdateStatus(std::string NewStatus)
    {
        Status = NewStatus;
    }
    
    ftxui::Component StatusBar;

private:
    std::string Status;
};
