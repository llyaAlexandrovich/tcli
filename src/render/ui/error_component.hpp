#pragma once



#include <iostream>
#include <string>
#include <chrono>
#include <format>


#include "ftxui/dom/elements.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/screen/screen.hpp"





class ErrorComponent
{
public:
    /**
     * Returns 'flood' component.
     * 
     * @author Ilya Alexandrovich
     * 
     * @param FloodMessage  message to display
     * @param TimeOut  time to display
     * 
     * @return return 'flood wait' component!
     * 
     * @since 1.0.0
     */
    ftxui::Component CreateFloodWaitComponent(std::string FloodMessage, std::chrono::seconds& TimeOut)
    {
        std::string FloodWaitPlaceHolder = "Flood Detected";


        std::string Status = "Telegram CLI";
        ftxui::Component StatusBar = ftxui::Renderer([&]
            {
                return ftxui::text(Status) | ftxui::hcenter;
            }
        );


        ftxui::Component PlaceHolderComponent = ftxui::Renderer([&]{
            return ftxui::paragraphAlignCenter(FloodWaitPlaceHolder + ": " + FloodMessage);
        });


        ftxui::Component Timer = ftxui::Renderer([&]
        {
            return ftxui::vbox(
                {
                    ftxui::text(std::format("Time left: {}", std::chrono::hh_mm_ss{TimeOut})) | ftxui::borderEmpty | ftxui::center,
                });
        });

        
        ftxui::Component FloodBox = ftxui::Container::Vertical(
        {
            PlaceHolderComponent,
            Timer
        }) | ftxui::border | ftxui::size(ftxui::WIDTH, ftxui::EQUAL, 32) | ftxui::size(ftxui::HEIGHT, ftxui::EQUAL, 15);


        ftxui::Component MainContent = ftxui::Container::Vertical(
        {
            StatusBar,
            FloodBox
        }) | ftxui::center | ftxui::focus;
        
        
        return MainContent;
    }
};
