#include "sdlFontRenderer.h"

sdlFontRenderer::sdlFontRenderer(SDL_Renderer* renderer) : m_renderer(renderer), m_font(nullptr)
{
    //ctor
}

sdlFontRenderer::~sdlFontRenderer()
{
    //dtor
}

void sdlFontRenderer::setFont(sdlFont* font)
{
    m_font = font;
}

void sdlFontRenderer::drawString(int x, int y, std::string text, int horizontalPosition, int verticalPosition)
{
    if (!m_font) return;
    unsigned renderedTextWidth  = getRenderedTextWidth(text);
    unsigned renderedTextHeight = m_font->getHeight();


    if (horizontalPosition == MIDDLE)
    {
        x -= renderedTextWidth / 2;
    }
    else if (horizontalPosition == RIGHT)
    {
        x -= renderedTextWidth;
    }

    if (verticalPosition == MIDDLE)
    {
        y -= renderedTextHeight / 2;
    }
    else if (verticalPosition == BOTTOM)
    {
        y -= renderedTextHeight;
    }



    for (unsigned i = 0; i < text.size(); ++i)
    {
        Image* img = m_font->getCharacter( text.at(i) );
        if (img)
        {
			img->renderImage(m_renderer, x, y);
			x += img->getWidth();
        }
    }

}

unsigned sdlFontRenderer::getRenderedTextWidth(std::string text)
{
    unsigned width = 0;

    if (!m_font) return width;

    for (unsigned i = 0; i < text.size(); ++i)
    {
        Image* img = m_font->getCharacter( text.at(i) );
        if (img)
        {
            width = img->getWidth();
        }
    }

    return width;
}


