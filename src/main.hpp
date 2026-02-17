#pragma once



#include <iostream>
#include <string>
#include <format>


#include "helper/helper.hpp"
#include "localization/localization.hpp"


#include "render/ui/ui_render.hpp"


#include "td/telegram/Client.h"
#include "td/telegram/td_api.h"
#include "td/telegram/td_api.hpp"


#include "types.hpp"
#include "tdhelper/tdtypes.hpp"


#include "tl/tl.hpp"


// !NOTE: -U, --proxy tokens are not supported yet.
/**
 * Recognizable arguments.
 * NONE => run program with the default settings
 * -H --help => show help page and exit
 * -U --user => specify the user for login
 * -L --language => specify language code
 * --proxy => specify proxy settings
 */
int main(int argc, char **argv);


// Version of TCli.
static std::string const VersionAsString = "1.0.0";
static int const VersionAsInt = CalculateVersion(VersionAsString);
static short const VersionAsIntMajor = (short)GetMajorVersion(VersionAsString);
static short const VersionAsIntMinor = (short)GetMinorVersion(VersionAsString);
static short const VersionAsIntPatch = (short)GetPatchVersion(VersionAsString);


// Help page content.
static std::string const HelpPageText = std::format("TCli v{} by Ilya Alexandrovich", VersionAsString);


// Debug.
#ifndef DEBUG
#define NDEBUG
#define DEBUG false
#endif
