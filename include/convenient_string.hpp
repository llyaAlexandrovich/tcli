#pragma once



#include <iostream>
#include <string>
#include <string_view>
#include <vector>






class convenient_string: public std::string
{
public:
    /**
     * Strip and then split a string using a custom delimiter and return
     * the resulting tokens. The internal contents of the string are not changed.
     * 
     * @author Ilya Alexandrovich
     * 
     * @param delimiter  the symbol to use as a delimiter for the string splitting
     * 
     * @return list of a resulting tokens
     * 
     * @since 1.0.0
     */
    [[nodiscard]]std::vector<std::string> extern_split(char const delimiter) noexcept
    {
        std::vector<std::string> output;
        std::string StrippedString = this->extern_strip();
        std::string word;

        for(int counter = 0; counter < this->length(); ++counter)
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
     * Split a string using a custom delimiter and rewrite current string content
     * as a list of tokens using space as the delimiter.
     * 
     * @author Ilya Alexandrovich
     * 
     * @param delimiter  the symbol to use as a delimiter for the string splitting
     * 
     * @return list of a resulting tokens
     * 
     * @since 1.0.0
     */
    [[noreturn]] void split(std::string const delimiter) noexcept
    {
        this->strip();

        for(int counter = 0; counter < this->length(); ++counter)
        {
            if(this[counter] == delimiter)
            {
                this->erase(counter, 1);
            }
        }
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
        for(int counter = 0; counter < output.length(); ++counter)
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
        for(int counter = 0; counter < this->length(); ++counter)
        {
            if(this[counter] == "\n" || this[counter] == "\r")
            {
                this->erase(counter, 1);
            }
        }
    }
};
