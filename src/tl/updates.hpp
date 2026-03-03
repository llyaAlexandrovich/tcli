#pragma once



#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <atomic>
#include <memory>
#include <thread>
#include <chrono>


#include "td/telegram/Client.h"
#include "td/telegram/td_api.h"
#include "td/telegram/td_api.hpp"


#include "types.hpp"
#include "tdhelper/tdtypes.hpp"


#include "chats.hpp"






/**
 * There's quite a lot of updates in Telegram so i decided
 * to manage them all separately.
 * 
 * @author Ilya Alexandrovich
 * 
 * @since 1.0.0  
 */
template <typename T>
class TelegramUpdates
{
public:
    TelegramUpdates();


    void InitTelegramUpdates()
    {
        TelegramCLI = static_cast<T*>(this);
    }


    // General updates

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
