#pragma once



#include <iostream>
#include <string>
#include <string_view>
#include <format>
#include <map>


#include "fs/fs.hpp"
#include "dotenv/dotenv.hpp"
#include "helper/helper.hpp"
#include "spdlog/spdlog.h"




/**
 * Recognizable arguments.
 * NONE => run program with the default settings
 * -H --help => show help page and exit
 * -U --user => specify the user for login
 * --proxy => specify proxy settings
 */
int main(int argc, char **argv);


// Version of TCli.
static std::string const StringVersion = "1.0.0";
static int const NumVersion = CalculateVersion(StringVersion);
static short const NumVersionMajor = (short)GetMajorVersion(StringVersion);
static short const NumVersionMinor = (short)GetMinorVersion(StringVersion);
static short const NumVersionPatch = (short)GetPatchVersion(StringVersion);


// Help page content.
static std::string const HelpPage = std::format("TCli v{} by Ilya Alexandrovich", StringVersion);



// Files program expect to access to.
static std::string const _EnvFileName = ".env";

