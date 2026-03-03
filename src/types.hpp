#pragma once



#include <iostream>
#include <string>


#include "helper/helper.hpp"


#define LANGUAGE_CODE "en"
#define LANGUAGE_CODE_IETF "en_US.UTF-8"



// Language code.
static std::string LanguageCode = []()
{
    std::string s = GetSystemLocale();
    if(!s.empty()) return s;
    else return LANGUAGE_CODE;
}();


// IETF locale.
static std::string LocaleIETF = []()
{
    std::string s = GetSystemLocaleWide();
    if(!s.empty()) return s;
    else return LANGUAGE_CODE_IETF;
}();
