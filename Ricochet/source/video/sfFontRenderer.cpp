#include "sfFontRenderer.h"

sfFontRenderer::sfFontRenderer()
{
    //ctor
}

sfFontRenderer::~sfFontRenderer()
{
    //dtor
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


    if (horizontalPosition == Align::MIDDLE)
    {
        x -= renderedTextWidth / 2;
    }
    else if (horizontalPosition == Align::RIGHT)
    {
        x -= renderedTextWidth;
    }
    if (verticalPosition == Align::MIDDLE)
    {
        y -= renderedTextHeight / 2;
    }
    else if (verticalPosition == Align::BOTTOM)
    {
        y -= renderedTextHeight;
    }



    for (unsigned i = 0; i < text.size(); ++i)
    {
        sf::Sprite* sprite = m_font->getCharacter( text.at(i) );
        if (sprite)
        {
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

void sfFontRenderer::setWindow(sf::RenderWindow* window)
{
    m_window = window;
}



