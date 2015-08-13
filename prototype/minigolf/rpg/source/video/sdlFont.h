#ifndef SDLFONT_H
#define SDLFONT_H

#include "sdl.h"

#include <vector>

#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <stdlib.h>

#include "video/image.h"

class sdlFont
{
    public:
        sdlFont();
        virtual ~sdlFont();
        // free resources
        void	free();

        // standard functions
        bool        loadFromFile(std::string path);
        Image*		getCharacter(int character);
        unsigned    getHeight();

    private:
        std::vector<Image*>   m_characters;

        template<typename T>
        std::string toString( const T& value );
};

#endif // SDLFONT_H
