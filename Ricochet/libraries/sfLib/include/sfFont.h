#ifndef SFFONT_H
#define SFFONT_H

#include "SFML/Window.hpp"
#include "SFML/Graphics.hpp"

#include <vector>

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <algorithm>

class sfFont
{
    public:
        sfFont();
        virtual ~sfFont();
        // free resources
        void            free();

        // standard functions
        bool            loadFromFile(std::string path);
        sf::Sprite*     getCharacter(int character);
        unsigned        getHeight();

    private:
        std::vector<sf::Sprite*>   m_characters;

        template<typename T>
        std::string toString( const T& value );
};

#endif // SFFONT_H
