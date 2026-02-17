#pragma once



#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <unordered_map>
#include <functional>
#include <memory>


#include "td/telegram/Client.h"
#include "td/telegram/td_api.h"
#include "td/telegram/td_api.hpp"


#include "types.hpp"
#include "tdhelper/tdtypes.hpp"


#include "chats.hpp"
#include "auth_updates.hpp"





/**
 * There's quite a lot of updates in Telegram so i decided
 * to manage all of them separately.
 * 
 * @author Ilya Alexandrovich
 * 
 * @since 1.0.0  
 */
template <typename T>
class TelegramUpdates : TelegramAuthUpdates
{
public:
    TelegramUpdates();


    void InitTelegramUpdates()
    {
        TelegramCLI = static_cast<T*>(this);
    }


    /**
     * Process Telegram updates.
     * 
     * @author Ilya Alexandrovich
     * 
     * @param Update  telegram update
     */
    void ProcessUpdate(TdObject Update)
    {

    }

private:
    T* TelegramCLI;




};
