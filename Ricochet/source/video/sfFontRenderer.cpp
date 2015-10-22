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

void sfFontRenderer::setRotation(float rotation)
{
    m_rotation = rotation;
}

float sfFontRenderer::getRotation()
{
    return m_rotation;
}

void sfFontRenderer::setTransparency(float transparency)
{
    m_transparency = transparency;
}

float sfFontRenderer::getTransparency()
{
    return m_transparency;
}


void sfFontRenderer::drawString(int x, int y, std::string text, int horizontalPosition, int verticalPosition)
{
    if (!m_font) return;
    unsigned renderedTextWidth  = getRenderedTextWidth(text);
    unsigned renderedTextHeight = m_font->getHeight();

    Vector2 pos(x,y);
    Vector2 dir(1,0);
    dir.rotate(-m_rotation);

    if (horizontalPosition == Align::MIDDLE)
    {
        Vector2 dir2 = dir;
        dir2.setMagnitude(renderedTextWidth / 2);
        pos -= dir2;
        //x -= renderedTextWidth / 2;
    }
    else if (horizontalPosition == Align::RIGHT)
    {
        Vector2 dir2 = dir;
        dir2.setMagnitude(renderedTextWidth);
        pos -= dir2;
        //x -= renderedTextWidth;
    }
    if (verticalPosition == Align::MIDDLE)
    {
        Vector2 dir2 = dir;
        dir2.rotate(90);
        dir2.setMagnitude(renderedTextHeight / 2);
        pos -= dir2;
        //y -= renderedTextHeight / 2;
    }
    else if (verticalPosition == Align::BOTTOM)
    {
        Vector2 dir2 = dir;
        dir2.rotate(90);
        dir2.setMagnitude(renderedTextHeight);
        pos -= dir2;
        //y -= renderedTextHeight;
    }

    for (unsigned i = 0; i < text.size(); ++i)
    {
        sf::Sprite* sprite = m_font->getCharacter( text.at(i) );
        if (sprite)
        {
            if (fmod(m_rotation,90) == 0) const_cast<sf::Texture*>(sprite->getTexture())->setSmooth(false);
            else                        const_cast<sf::Texture*>(sprite->getTexture())->setSmooth(true);

            m_color.a = m_transparency;
            sprite->setRotation(-m_rotation);
            sprite->setColor(m_color);
            sprite->setPosition(pos.x,pos.y);
            dir.setMagnitude(sprite->getTexture()->getSize().x);
            pos += dir;
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



