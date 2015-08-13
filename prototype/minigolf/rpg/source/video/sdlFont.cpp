#include "sdlFont.h"

sdlFont::sdlFont()
{
    //ctor
}

sdlFont::~sdlFont()
{
    //dtor
}

void sdlFont::free()
{
    for (unsigned i = 0; i < m_characters.size(); ++i)
    {
		m_characters.at(i)->freeTexture();
        delete m_characters.at(i);
        m_characters.at(i) = nullptr;
    }
    m_characters.clear();
}

bool sdlFont::loadFromFile(std::string path)
{
    bool success = true;
    free();

    for (unsigned i = 32; i <= 126; ++i)
    {
        std::string fileName = path + toString(i) + ".png";
        Image* img = new Image();
		if (!img->loadTexture(fileName))
		{
			cout << "error loading image: " << fileName << endl;
			success = false;
		}

		m_characters.push_back(img);
    }
    return success;
}

Image* sdlFont::getCharacter(int character)
{
    character -= 32;
    if ( character < 0 || character > 94 )  return nullptr;
    if ( m_characters.size() == 0 )         return nullptr;

    return m_characters.at(character);
}

unsigned sdlFont::getHeight()
{
    if (m_characters.size() == 0)   return 0;
    return m_characters.at(0)->getWidth();
}

/////////////////////////////////////////////
// *** toString Function ***
/////////////////////////////////////////////
template<typename T>
std::string sdlFont::toString( const T& value )
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

