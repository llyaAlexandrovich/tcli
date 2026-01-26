#pragma once



#include <iostream>
#include <string>
#include <string_view>


#include "fs/fs.hpp"
#include "spdlog/spdlog.h"



[[nodiscard]]bool IsValidTDF(std::string_view FIleName) noexcept;