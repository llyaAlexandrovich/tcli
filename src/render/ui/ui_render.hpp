#pragma once



#include <iostream>
#include <string>
#include <functional>


#include "localization/localization.hpp"


#include "td/telegram/Client.h"
#include "td/telegram/td_api.h"
#include "td/telegram/td_api.hpp"


#include "ftxui/dom/elements.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/screen/screen.hpp"


#include "types.hpp"
#include "tdhelper/tdtypes.hpp"


#include "auth_component.hpp"






class UIRender : public AuthComponent
{
public:
    enum class SceneType : int
    {
        None = 0,
        Main,
        AuthorizationByPhoneNumber,
        AuthorizationByEmailAddress,
        Blank
    };



    /**
     * Render scene with the given type.
     * 
     * @author Ilya Alexandrovich
     * 
     * @param Type  scene type
     * 
     * @since 1.0.0
     */
    void RenderScene(SceneType Type, std::string& InputContent, bool& bisChangeRequired, std::string Content)
    {
        CurrentSceneType = Type;
        switch(Type){
            case SceneType::None:
                break;
            case SceneType::Main:
                break;
            case SceneType::AuthorizationByPhoneNumber:
                {
                    auto ActiveComponent = CreatePhoneAuthComponent(InputContent);
                    std::thread UIThread([&]{
                        Screen.Loop(ActiveComponent);
                    });
                }
                break;
            case SceneType::AuthorizationByEmailAddress:
                {
                    auto ActiveComponent = CreateEmailAuthComponent(InputContent);
                    std::thread UIThread([&]{
                        Screen.Loop(ActiveComponent);
                    });
                }
                break;
            case SceneType::Blank:
                std::thread UIThread([&]{
                    Screen.Loop(BlankComponent);
                });
                break;
        };
    }



    /**
     * If some scene won't exit themselves don't be ease on them.
     * 
     * @author Ilya Alexandrovich
     * 
     * @since 1.0.0
     */
    void ExitScene()
    {
        Screen.Post([&] { Screen.Exit(); });
    }



    /**
     * This funciton update current state and scene if exists.
     * 
     * @author Ilya Alexandrovich
     * 
     * @param Type  scene type
     * @param SceneInputHandler  callback for when user done with input and press enter
     * 
     * @since 1.0.0
     */
    void UpdateScene(SceneType Type, std::function<bool()> SceneInputHandler)
    {
        if(CurrentSceneType != SceneType::None) ExitScene();
        RenderScene(Type, SceneInputHandler);
    }



private:
    ftxui::ScreenInteractive Screen = ftxui::ScreenInteractive::Fullscreen();


    SceneType CurrentSceneType = SceneType::None;


    ftxui::Component BlankComponent = ftxui::Renderer([]{
        return ftxui::text("");
    });
};


//ftxui::Component ChatSelector = ftxui::Menu() | ftxui::frame | ftxui::vscroll_indicator;
