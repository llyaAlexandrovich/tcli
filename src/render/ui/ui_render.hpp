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
     * @param Parameters  reference to an existing EmailParameters struct
     * 
     * @since 1.0.0
     */
    void RenderEmailAuthScene(EmailParameters& Parameters)
    {
        ExitScene();
        ftxui::Component ActiveComponent = CreateEmailAuthorizationComponent(Parameters);
        std::thread UIThread([&]{
            Screen.Loop(ActiveComponent);
        });
    }



    /**
     * Renders phone auth page.
     * 
     * @author Ilya Alexandrovich
     * 
     * @param Parameters  reference to an existing PhoneParameters struct
     * 
     * @since 1.0.0
     */
    void RenderPhoneAuthScene(PhoneParameters& Parameters)
    {
        ExitScene();
        ftxui::Component ActiveComponent = CreatePhoneAuthorizationComponent(Parameters);
        std::thread UIThread([&]{
            Screen.Loop(ActiveComponent);
        });
    }



    /**
     * Renders password auth page.
     * 
     * @author Ilya Alexandrovich
     * 
     * @param Parameters  reference to an existing PasswordParameters struct
     */
    void RenderPasswordAuthScene(PasswordParameters& Parameters)
    {
        ExitScene();
        ftxui::Component ActiveComponent = CreatePasswordAuthComponent(Parameters);
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
