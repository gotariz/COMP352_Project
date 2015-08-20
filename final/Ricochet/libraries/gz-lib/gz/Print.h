#ifndef PRINT_H_INCLUDED
#define PRINT_H_INCLUDED

//////////////////////////////////////////
// HEADERS
//////////////////////////////////////////
#include <iostream>

namespace gz
{
    //////////////////////////////////////////
    // DECLARATION
    //////////////////////////////////////////
    void print_l(std::string text); // line
    void print_d(std::string text); // debug
    void print_m(std::string text); // message
    void print_w(std::string text); // warning
    void print_s(std::string text); // success
    void print_f(std::string text); // failure
    void print_value(std::string text, double value);

    //////////////////////////////////////////
    // IMPLEMENTATION
    //////////////////////////////////////////
    inline void print_l(std::string text)
    {
        std::cout << text << std::endl;
    }

    inline void print_d(std::string text)
    {
        std::cout << "Debug\t- " << text << std::endl;
    }

    inline void print_m(std::string text)
    {
        std::cout << "Message\t- " << text << std::endl;
    }

    inline void print_w(std::string text)
    {
        std::cout << "Warning\t- " << text << std::endl;
    }

    inline void print_s(std::string text)
    {
        std::cout << "Success\t- " << text << std::endl;
    }

    inline void print_f(std::string text)
    {
        std::cout << "Failure\t- " << text << std::endl;
    }

    inline void print_value(std::string text, double value)
    {
        std::cout << text << value << std::endl;
    }

}


#endif // PRINT_H_INCLUDED
