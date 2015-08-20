#ifndef GZ_UTILS_H_INCLUDED
#define GZ_UTILS_H_INCLUDED

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <algorithm>

namespace gz
{

    ////////////////////////////////////////////////////////////
    /// \brief returns the string located from index start to end
    ///
    /// \param str      the string to split
    /// \param start    the index of the first char to return
    /// \param end      the index of the last char to return
    ///
    /// \return         the string located from index "start" to "end"
    ////////////////////////////////////////////////////////////
    std::string subString( const std::string& str, unsigned int start, unsigned int end);

    ////////////////////////////////////////////////////////////
    /// \brief returns the bool equivalent of the string
    ///
    /// \param str      the string evaluate
    ///
    /// \return         the bool equivalent of the string
    ////////////////////////////////////////////////////////////
    bool toBool(const char* text);

    ////////////////////////////////////////////////////////////
    /// \brief convert all the characters of a string to
    ///        lower-case
    ///
    /// \param str      the string to convert to lower-case
    ///
    /// \return         the string in lower-case characters
    ////////////////////////////////////////////////////////////
    std::string& toLowerCase( std::string& str );

    ////////////////////////////////////////////////////////////
    /// \brief convert all the characters of a string to
    ///        upper-case
    ///
    /// \param  str  the string to convert to upper-case
    ///
    /// \return the string in upper-case characters
    ////////////////////////////////////////////////////////////
    std::string& toUpperCase( std::string& str );

    ////////////////////////////////////////////////////////////
    /// \brief returns the string representation of a boolean.
    ///        "true" or "false"
    ///
    /// \param value    the boolean value to convert
    ///
    /// \return         the boolean represented as a string
    ////////////////////////////////////////////////////////////
    template<bool>
    std::string toString( const bool& value );

    ////////////////////////////////////////////////////////////
    /// \brief returns the char as a string
    ///
    /// \param value    the char to convert
    ///
    /// \return         the char value as a string
    ////////////////////////////////////////////////////////////
    template<char>
    std::string toString( const char& value );

    ////////////////////////////////////////////////////////////
    /// \brief returns the data as a string
    ///
    /// \param value    the value/data to convert
    ///
    /// \return         the converted value/data as a string
    ////////////////////////////////////////////////////////////
    template<typename T>
    std::string toString( const T& value );

    ////////////////////////////////////////////////////////////
    /// \brief converts a float into a string. prec = decimal precision
    ///
    /// \param value    the value to convert
    ///
    /// \return         the value as a string
    ////////////////////////////////////////////////////////////
    std::string toStringFloat( const float& value, unsigned prec = 0 );

    ////////////////////////////////////////////////////////////
    /// \brief convert string to a positive.
    ///
    /// \param str: the string to convert
    ///
    /// \return the positive int or -1 if failed
    ////////////////////////////////////////////////////////////
    int stringToUnsigned(std::string str);

    ////////////////////////////////////////////////////////////
    /// \brief splits a string into a name and value using the
    /// first "=" symbol
    ///
    /// \param line: the line of text that will be used
    ///
    /// \return the name and value extracted from the string
    ////////////////////////////////////////////////////////////
    std::pair<std::string,std::string> getValuePair(std::string line);

    ////////////////////////////////////////////////////////////
    /// \brief returns that index for the last occurance of the
    /// character
    ///
    /// \param text: the line of text that will be used
    /// \param target: the character to get the last index of
    ///
    /// \return the index for the last occurance of the character
    ////////////////////////////////////////////////////////////
    int lastIndexOf(std::string text, char target);

    ////////////////////////////////////////////////////////////
    /// \brief returns that index for the first occurance of the
    /// character
    ///
    /// \param text: the line of text that will be used
    /// \param target: the character to get the first index of
    ///
    /// \return the index for the first occurance of the character
    ////////////////////////////////////////////////////////////
    int firstIndexOf(std::string text, char target);

    ////////////////////////////////////////////////////////////
    /// \brief returns that fileName from the directory
    ///
    /// \param text: the directory as a string
    ///
    /// \return the fileName from the file directory
    ////////////////////////////////////////////////////////////
    std::string getFileName(std::string path);

    ////////////////////////////////////////////////////////////
    /// \brief returns that file extension from the directory
    ///
    /// \param text: the directory as a string
    ///
    /// \return the extension from the file directory
    ////////////////////////////////////////////////////////////
    std::string getFileExtension(std::string path);

    //TODO:: documentation for these!
    std::string replaceInstancesOf(std::string text, char oldChar, char newChar);
    std::vector<std::string> splitString(std::string path, char delimeter);
    int toInt(const char* str,int defaultValue);

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // Inline Implementations
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    ////////////////////////////////////////////////////////////
    inline std::string subString( const std::string& str, unsigned int start, unsigned int end)
    {
        if (end >= str.length()) end = str.length() - 1;
        if (start > end) return "";

        std::string subStr;
        for (unsigned i = start; i <= end; ++i)
        {
            subStr.push_back( str[i] );
        }
        return subStr;
    }

    ////////////////////////////////////////////////////////////
    inline int stringToUnsigned(std::string str)
    {
        for(unsigned i = 0; i < str.length(); ++i)
        {
            if (str[i] < 48 || str[i] > 58)
                return -1;
        }

        return atoi(str.c_str());
    }

    ////////////////////////////////////////////////////////////
    inline bool toBool(const char* text)
    {
        if (text == NULL) return false;

        std::string str = text;
        if (str.size() == 0) return false;
        str = toUpperCase(str);
        char firstChar = str.at(0);
        if (firstChar == 'F' || firstChar == '0') return false;

        return true;
    }

    ////////////////////////////////////////////////////////////
    inline std::string& toLowerCase( std::string& str )
    {
        for ( std::string::iterator iter = str.begin(); iter != str.end(); ++iter )
            *iter = tolower( *iter );
        return str;

    }

    ////////////////////////////////////////////////////////////
    inline std::string& toUpperCase( std::string& str )
    {
        transform( str.begin(), str.end(), str.begin(), toupper );
        // passing the address of the C toupper() function to transform()
        return str;
    }

    ////////////////////////////////////////////////////////////
    template<bool>
    inline std::string toString( const bool& value )
    {
        std::ostringstream oss;
        try
        {
            // Turn on exceptions
            oss.exceptions( std::ios::badbit | std::ios::failbit );
            oss << std::boolalpha << value;
        }
        catch ( std::ios_base::failure e )
        {
            std::cerr << e.what() << std::endl;
            // clear the ostream
            oss.clear( std::ios::goodbit );
            return "";
        }
        return oss.str();
    }

    ////////////////////////////////////////////////////////////
    template<char>
    inline std::string toString( const char& value )
    {
        std::string rtn;
        rtn.append( std::string(value) );
        return rtn;
    }

    ////////////////////////////////////////////////////////////

    template<typename T>
    inline std::string toString( const T& value )
    {
        std::ostringstream oss;
        try
        {
            // Turn on exceptions
            oss.exceptions( std::ios::badbit | std::ios::failbit );
            oss << value;
        }
        catch ( std::ios_base::failure e )
        {
            std::cerr << e.what() << std::endl;
            // clear the ostream
            oss.clear( std::ios::goodbit );
            return "";
        }
        return oss.str();
    }

    ////////////////////////////////////////////////////////////
    inline std::string toStringFloat( const float& value, unsigned fractionSize )
    {
        // override default compiler value with system limit for base 10 number
        int prec = std::numeric_limits<float>::digits10;

        std::ostringstream oss;
        // this is total number of digits not just the decimal fraction part
        oss.precision( prec );
        try
        {
            // Turn on exceptions
            oss.exceptions( std::ios::badbit | std::ios::failbit );
            oss << value;
        }
        catch ( std::ios_base::failure e )
        {
            std::cerr << e.what() << std::endl;
            // clear the ostream
            oss.clear( std::ios::goodbit );
            return "";
        }
        // extract the string from the stream
        std::string strFloat = oss.str();
        // To format it, first find the (english) decimal place
        size_t pointPos = strFloat.find( '.' );
        // if there is a decimal point
        //TODO doesn't erase the . when nothing after it
        if ( ( pointPos != std::string::npos ) &&
                // and it is followed by at least fractionSize digits
                ( strFloat.size() > pointPos + fractionSize ) )
        {
            std::string temp = strFloat.substr( 0, ++pointPos + fractionSize );
            strFloat = temp;
        }
        return strFloat;
    }

    ////////////////////////////////////////////////////////////
    inline std::pair<std::string,std::string> getValuePair(std::string line)
    {
        std::string name = "";
        std::string value ="";
        bool readingName = true;

        for (unsigned i = 0; i < line.size(); ++i)
        {
            char c = line.at(i);
            if ( c == '=')
            {
                readingName = false;
                continue;
            }

            if (readingName) name.append( gz::toString(c) );
            else value.append( gz::toString(c) );
        }

        return std::pair<std::string,std::string>(name,value);
    }

    ////////////////////////////////////////////////////////////
    inline int lastIndexOf(std::string text, char target)
    {
        int result = -1;
        for (int i = text.length() - 1; i > 0; --i)
        {
            if (text.at(i) == target)
            {
                result = i;
                i = 0;
            }
        }
        return result;
    }

    ////////////////////////////////////////////////////////////
    inline int firstIndexOf(std::string text, char target)
    {
        int result = -1;
        for (unsigned i = 0; i < text.length() - 1; ++i)
        {
            if (text.at(i) == target)
            {
                result = i;
                i = text.length();
            }
        }
        return result;
    }

    ////////////////////////////////////////////////////////////
    inline std::vector<std::string> splitString(std::string path, char delimeter)
    {
        std::vector<std::string> result;
        std::string current_word = "";

        for(unsigned i = 0; i < path.length(); ++i)
        {
            char current_char = path.at(i);
            if (current_char != delimeter)
            {
                current_word.append( gz::toString(current_char) );
            }

            if ( (current_char == delimeter && current_word != "") || (i == path.length() - 1))
            {
                result.push_back(current_word);
                current_word = "";
            }
        }

        return result;
    }

    ////////////////////////////////////////////////////////////
    inline std::string replaceInstancesOf(std::string text, char oldChar, char newChar)
    {
        for (unsigned i = 0; i < text.length(); ++i)
        {
            if (text.at(i) == oldChar) {text.at(i) = newChar;}
        }

        return text;
    }

    ////////////////////////////////////////////////////////////
    inline std::string getFileName(std::string path)
    {
        std::string last_word = gz::splitString(path,'/').back();
        int last_index = gz::lastIndexOf(last_word,'.');

        if (last_index > 0) last_index -= 1;
        else                last_index = last_word.length() - 1;

        return gz::subString(last_word,0,last_index);
    }

    ////////////////////////////////////////////////////////////
    inline std::string getFileExtension(std::string path)
    {
        std::string last_word = gz::splitString(path,'/').back();
        int start_index = gz::lastIndexOf(last_word,'.');

        int last_index = last_word.length() - 1;
        if (start_index > last_index) start_index = 0;

        return gz::subString(last_word,start_index,last_index);
    }

    ////////////////////////////////////////////////////////////
    inline int toInt(const char* str,int defaultValue) // default string to int cast
    {
        if (str == NULL) return defaultValue;

        int number = atoi(str);
        std::string original_string = str;
        std::string number_string = toString(number);
        int result = defaultValue;

        if (number_string == original_string)
        {
            result = number;
        }

        return result;
    }

}
#endif // GZ_UTILS_H_INCLUDED
