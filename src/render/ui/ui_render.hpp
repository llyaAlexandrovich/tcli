#pragma once



#include <iostream>
#include <string>
#include <atomic>


#include "ftxui/dom/elements.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/screen/screen.hpp"


#include "auth_component.hpp"



// See examples at doc/UI/Rendering .
class UIRender : public AuthComponent
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
     * @param OnDetailsChange  trigger showing whether user is requested details change
     * @param ValidationFailedActive  this trigger allows to activate ValidationFailed component inside current form
     * 
     * @since 1.0.0
     */
    void RenderEmailCodeAuthScene(std::string& InputContent, std::atomic<bool>& OnProcess, std::atomic<bool>& OnDetailsChange, std::atomic<bool>& ValidationFailedActive)
    {
        ExitScene();
        ftxui::Component ActiveComponent = CreateEmailAuthCodeComponent(InputContent, OnProcess, OnDetailsChange, ValidationFailedActive);
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
        ftxui::Component ActiveComponent = CreatePasswordComponent(InputContent, OnProcess, ValidationFailedActive);
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
