#include "auth.hpp"








namespace auth
{
    [[nodiscard]] bool IsAuthorized() noexcept
    {
        if(fs::IsFileExists("data/auth"))
        {
            return true;
        }
        return false;
    }
}