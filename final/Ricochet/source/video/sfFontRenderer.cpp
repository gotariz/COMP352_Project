#include "sfFontRenderer.h"

sfFontRenderer::sfFontRenderer(sf::RenderWindow* window) : m_window(window), m_font(nullptr)
{
    //ctor
}

sfFontRenderer::~sfFontRenderer()
{
    //dtor
}

void sfFontRenderer::setWindow(sf::RenderWindow* window)
{
    m_window = window;
}

void sfFontRenderer::setFont(sfFont* font)
{
    m_font = font;
}

void sfFontRenderer::setColor(sf::Color c)
{
    m_color = c;
}

void sfFontRenderer::drawString(int x, int y, std::string text, int horizontalPosition, int verticalPosition)
{
    if (!m_font) return;
    unsigned renderedTextWidth  = getRenderedTextWidth(text);
    unsigned renderedTextHeight = m_font->getHeight();


    if (horizontalPosition == sfLib::sfAlign::MIDDLE)
    {
        x -= renderedTextWidth / 2;
    }
    else if (horizontalPosition == sfLib::sfAlign::RIGHT)
    {
        x -= renderedTextWidth;
    }
    if (verticalPosition == sfLib::sfAlign::MIDDLE)
    {
        y -= renderedTextHeight / 2;
    }
    else if (verticalPosition == sfLib::sfAlign::BOTTOM)
    {
        y -= renderedTextHeight;
    }



    for (unsigned i = 0; i < text.size(); ++i)
    {
        sf::Sprite* sprite = m_font->getCharacter( text.at(i) );
        if (sprite)
        {
            //cout << m_color.r << "," << m_color.g << "," << m_color.b << "," << m_color.a << endl;
            sprite->setColor(m_color);
            sprite->setPosition(x,y);
            x += sprite->getTexture()->getSize().x;
            m_window->draw( *sprite );
        }
    }

}

unsigned sfFontRenderer::getRenderedTextWidth(std::string text)
{
    unsigned width = 0;

    if (!m_font) return width;

    for (unsigned i = 0; i < text.size(); ++i)
    {
        sf::Sprite* sprite = m_font->getCharacter( text.at(i) );
        if (sprite)
        {
            width += sprite->getTexture()->getSize().x;
        }
    }

    return width;
}


