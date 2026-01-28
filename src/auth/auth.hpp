#pragma once



#include <iostream>
#include <string>
#include <string_view>


#include "fs/fs.hpp"
#include "openssl/openssl/md5.h"




namespace auth
{
    /**
     * Check whether user is authorized by checking existence of the
     * required configs that contains user auth data.
     */
    [[nodiscard]] bool IsAuthorized() noexcept;






} // namespace auth