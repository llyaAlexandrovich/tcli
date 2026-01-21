#pragma once



#include <iostream>
#include <string>
#include <string_view>
#include <vector>

#include "fs/fs.hpp"



[[nodiscard]]bool IsConfigsExists(std::vector<std::string> ConfigsNames) noexcept; 