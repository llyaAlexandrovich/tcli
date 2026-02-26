#pragma once



#include <iostream>
#include <string>
#include <atomic>
#include <chrono>


#include "ftxui/dom/elements.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/screen/screen.hpp"


#include "auth_component.hpp"
#include "error_component.hpp"



// See examples at doc/UI/Rendering .
class UIRender : public AuthComponent, public ErrorComponent
{
public:
    /**
     * Renders email auth page.
     * 
     * @author Ilya Alexandrovich
     * 
     * @param InputContent  reference to an editable string to write content to
     * @param OnProcess  trigger of whether input is validated and could be used
     * 
     * @since 1.0.0
     */
    void RenderEmailAuthScene(std::string& InputContent, std::atomic<bool>& OnProcess)
    {
        ExitScene();
        ftxui::Component ActiveComponent = CreateEmailAuthComponent(InputContent, OnProcess);
        std::thread UIThread([&]{
            Screen.Loop(ActiveComponent);
        });
    }
    


    /**
     * Renders email code auth page.
     * 
     * @author Ilya Aleandrovich
     * 
     * @param InputContent  reference to an editable string to write content to
     * @param OnProcess  trigger of whether input is validated and could be used
     * @param EmailPlaceHolder  fancy email place holder
     * @param ValidationFailedActive  this trigger allows to activate ValidationFailed component inside current form
     * 
     * @since 1.0.0
     */
    void RenderEmailCodeAuthScene(std::string& InputContent, std::atomic<bool>& OnProcess, std::string& EmailPlaceHolder, std::atomic<bool>& ValidationFailedActive)
    {
        ExitScene();
        ftxui::Component ActiveComponent = CreateEmailAuthCodeComponent(InputContent, OnProcess, EmailPlaceHolder, ValidationFailedActive);
        std::thread UIThread([&]{
            Screen.Loop(ActiveComponent);
        });
    }



    /**
     * Renders phone auth page.
     * 
     * @author Ilya Alexandrovich
     * 
     * @param InputContent  reference to an editable string to write content to
     * @param OnProcess  trigger of whethe input is validated and could be used
     * 
     * @since 1.0.0
     */
    void RenderPhoneAuthScene(std::string& InputContent, std::atomic<bool>& OnProcess)
    {
        ExitScene();
        ftxui::Component ActiveComponent = CreatePhoneAuthComponent(InputContent, OnProcess);
        std::thread UIThread([&]{
            Screen.Loop(ActiveComponent);
        });
    }



    /**
     * Renders phone code auth page.
     * 
     * @author Ilya Alexandrovich
     * 
     * @param InputContent  reference to an editable string to write content to
     * @param OnProcess  trigger of whether input is validated and could be used
     * @param OnDetailsChange  trigger showing whether user is requested details change
     * @param ValidationFailedActive  this trigger allows to activate ValidationFailed component inside current form
     * 
     * @since 1.0.0
     */
    void RenderPhoneCodeAuthScene(std::string& InputContent, std::atomic<bool>& OnProcess, std::atomic<bool>& OnDetailsChange, std::atomic<bool>& ValidationFailedActive)
    {
        ExitScene();
        ftxui::Component ActiveComponent = CreatePhoneAuthCodeComponent(InputContent, OnProcess, OnDetailsChange, ValidationFailedActive);
        std::thread UIThread([&]{
            Screen.Loop(ActiveComponent);
        });
    }



    /**
     * Renders password auth page.
     * 
     * @author Ilya Alexandrovich
     * 
     * @param InputContent  reference to an editable string to write content to
     * @param Onprocess  trigger of whether input is validated and could be used
     * @param ValidationFailedActive  this trigger allows to activate ValidationFailed component inside current form
     */
    void RenderPasswordAuthScene(std::string& InputContent, std::atomic<bool>& OnProcess, std::atomic<bool>& ValidationFailedActive)
    {
        ExitScene();
        ftxui::Component ActiveComponent = CreatePasswordAuthComponent(InputContent, OnProcess, ValidationFailedActive);
        std::thread UIThread([&]{
            Screen.Loop(ActiveComponent);
        });
    }



    /**
     * Renders flood wait error page.
     * 
     * @author Ilya Alexandrovich
     * 
     * @param FloodMessage  message to show in the scene body
     * @param TimeOut  time to display in the scene counter
     * 
     * @since 1.0.0
     */
    void RenderFloodWaitScene(std::string& FloodMessage, std::chrono::seconds& TimeOut)
    {
        ExitScene();
        ftxui::Component ActiveComponent = CreateFloodWaitComponent(FloodMessage, TimeOut);
        std::thread UIThread([&]{
            Screen.Loop(ActiveComponent);
        });
        while(TimeOut != TimeOut.zero())
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
            --TimeOut;
            Screen.PostEvent(ftxui::Event::Custom);
        }
    }



    /**
     * Renders waiting for premium page.
     * 
     * @author Ilya Alexandrovich
     * 
     * @since 1.0.0
     */
    void RenderPremiumRequiredAuthScene()
    {
        ExitScene();
        ftxui::Component ActiveComponent = CreatePremiumRequiredAuthComponent();
        std::thread UIThread([&]{
            Screen.Loop(ActiveComponent);
        });
    }


private:
    ftxui::ScreenInteractive Screen = ftxui::ScreenInteractive::Fullscreen();

    // Exit current scene.
    void ExitScene()
    {
        Screen.Post([&] { Screen.Exit(); });
    }
};
