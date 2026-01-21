#pragma once



#include <iostream>
#include <string>
#include <string_view>
#include <sstream>
#include <vector>
#include <map>


#include "fs/fs.hpp"
#include "convenient_string.hpp"




/**
 * Read the environment file and set up its data.
 * 
 * @author Ilya Alexandrovich
 * 
 * @param FileName  read-only name of the file
 * @param EnvContent map<string, string> variable in which to store the data
 * 
 * @since 1.0.0
 */
[[nodiscard]]void LoadEnvVariables(std::string_view FileName, std::map<std::string, std::string> EnvContent) noexcept;


// TODO: Add support of the internal environment.