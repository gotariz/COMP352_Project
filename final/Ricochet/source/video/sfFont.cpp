#include "sfFont.h"

sfFont::sfFont()
{
    //ctor
}

sfFont::~sfFont()
{
    //dtor
}

void sfFont::free()
{
    for (unsigned i = 0; i < m_characters.size(); ++i)
    {
		delete m_characters.at(i)->getTexture();
        delete m_characters.at(i);
        m_characters.at(i) = nullptr;
    }
    m_characters.clear();
}

bool sfFont::loadFromFile(std::string path)
{
    bool no_errors = true;
    free();

    for (unsigned i = 32; i < 126; ++i)
    {
        std::string fileName = path + toString(i) + ".png";
        sf::Texture* texture = new sf::Texture;
        if (!texture->loadFromFile(fileName)) no_errors = false;

        sf::Sprite* sprite = new sf::Sprite;
        sprite->setTexture( *texture );

        m_characters.push_back(sprite);
    }

    return no_errors;
}

sf::Sprite* sfFont::getCharacter(int character)
{
    character -= 32;
    if ( character < 0 || character > 94 )  return nullptr;
    if ( m_characters.size() == 0 )         return nullptr;

    return m_characters.at(character);
}

unsigned sfFont::getHeight()
{
    if (m_characters.size() == 0)   return 0;
    return m_characters.at(0)->getTexture()->getSize().y;
}

/////////////////////////////////////////////
// *** toString Function ***
/////////////////////////////////////////////
template<typename T>
std::string sfFont::toString( const T& value )
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

