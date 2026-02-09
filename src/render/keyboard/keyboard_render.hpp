#pragma once



#include <iostream>
#include <sstream>
#include <functional>
#include <string>
#include <string_view>
#include <map>
#include <unordered_map>
#include <ranges>
#include <memory>
#include <vector>








class KeyBoardRender
{
public:
    KeyBoardRender()
    {

    }



    /**
     * Register keys and callbacks for when keys is pressed. ALready existing keys
     * re-registering.
     * 
     * @author Ilya Alexandrovich
     * 
     * @param KeyList  buffer of keys to register
     * @param callback  function-callback
     * 
     * @since 1.0.0
     */
    void RegisterKeys(std::vector<int>&& KeyList, std::vector<std::function<void()>>&& callbacks) noexcept
    {
        std::size_t count = std::min(KeyList.size(), callbacks.size());

        keys.reserve(keys.size() + count);
    
        for(std::size_t i = 0; i < count; ++i)
        {
            keys[KeyList[i]] = std::move(callbacks[i]);
        }
    }



    /**
     * Unregister given keys.
     * 
     * @author Ilya Alexandrovich
     * 
     * @param KeyList  buffer of keys to unregister
     * 
     * @since 1.0.0
     */
    void UnregisterKeys(const std::vector<int>& KeyList) noexcept
    {
        for (const auto k : KeyList) {
            keys.erase(k);
        }
    }


private:
    //struct 


    std::unordered_map<int, std::function<void()>> keys;


    /**
     * 
     */
    // void 

};
