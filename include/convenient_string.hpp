#pragma once



#include <iostream>
#include <string>
#include <string_view>
#include <vector>
#include <cctype>





class convenient_string: public std::string
{
public:
    /**
     * Strip and then split a string using a custom delimiter and return
     * the resulting tokens. The internal contents of the string are not changed.
     * 
     * @author Ilya Alexandrovich
     * 
     * @param delimiter  the symbol to use as the delimiter for the string splitting
     * 
     * @return list of a resulting tokens
     * 
     * @since 1.0.0
     */
    [[nodiscard]] std::vector<std::string> split(char const delimiter) noexcept
    {
        std::vector<std::string> output;
        std::string StrippedString;
        StrippedString.assign(this->data());
        std::string word;

        for(int counter = 0; counter != this->length(); ++counter)
        {
            if(StrippedString[counter] == delimiter)
            {
                output.push_back(word);
                word.erase();
            }
            else
            {
                word += StrippedString[counter];
            }
        }
        return output;
    }



    /**
     * Exclude all the control symbols such as \n and \r from the string content.
     * Return the resulting string.
     * 
     * @author Ilya Alexandrovich
     * 
     * @return return the stripped string
     * 
     * @since 1.0.0
     */
    [[nodiscard]] std::string extern_strip() noexcept
    {
        std::string output;
        output.assign(this->data());
        for(int counter = 0; counter != output.length(); ++counter)
        {
            if(output[counter] == '\n' || output[counter] == '\r')
            {
                output.erase(counter, 1);
            }
        }
        return output;
    }



    /**
     * Exclude all control the symbols such as \n and \r from the string content.
     * Current string content will be modified.
     * 
     * @author Ilya Alexandrovich
     * 
     * @since 1.0.0
     */
    [[noreturn]] void strip() noexcept
    {
        for(int counter = 0; counter != this->length(); ++counter)
        {
            if(this[counter] == "\n" || this[counter] == "\r")
            {
                this->erase(counter, 1);
            }
        }
    }



    /**
     * Convert string characters to lower.
     * 
     * @author Ilya Alexandrovich
     * 
     * @since 1.0.0
     */
    [[noreturn]] void to_lower() noexcept
    {
        std::transform(this->begin(), this->end(), this->begin(), [](unsigned char c){ return std::tolower(c); });
    }


    
    /**
     * Convert characters to lower and return resulting string.
     * 
     * @author Ilya Alexandrovich
     * 
     * @return return string with all characters set as lower
     * 
     * @since 1.0.0
     */
    [[nodiscard]] std::string extern_to_lower() noexcept
    {
        std::string output;
        output.assign(this->data());

        std::transform(output.begin(), output.end(), output.begin(), [](unsigned char c){ return std::tolower(c); });

        return output;
    }



    /**
     * Convert string characters to upper.
     * 
     * @author Ilya Alexandrovich
     * 
     * @since 1.0.0
     */
    [[noreturn]] void to_upper() noexcept
    {
        std::transform(this->begin(), this->end(), this->begin(), [](unsigned char c){ return std::toupper(c); });
    }



    /**
     * Convert characters to upper and return resulting string.
     * 
     * @author Ilya Alexandrovich
     * 
     * @return return string with all characters set as upper
     * 
     * @since 1.0.0
     */
    [[nodiscard]] std::string extern_to_upper() noexcept
    {
        std::string output;
        output.assign(this->data());

        std::transform(output.begin(), output.end(), output.begin(), [](unsigned char c){ return std::toupper(c); });

        return output;
    }
};
