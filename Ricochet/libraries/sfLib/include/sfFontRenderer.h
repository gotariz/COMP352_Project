#ifndef SFFONTRENDERER_H
#define SFFONTRENDERER_H

#include <string>

#include "sfLib.h"

namespace sfLib
{
    enum sfAlign
    {
        LEFT,
        RIGHT,
        TOP,
        BOTTOM,
        MIDDLE,
    };
}

class sfFontRenderer
{
    public:
        sfFontRenderer(sf::RenderWindow* window);
        virtual ~sfFontRenderer();

    public:
        void setFont(sfFont* font);
        void drawString(int x, int y, std::string text, int horizontalPosition = sfLib::sfAlign::LEFT, int verticalPosition = sfLib::sfAlign::TOP);

        unsigned getRenderedTextWidth(std::string text);

    private:
        sf::RenderWindow*   m_window;
        sfFont*             m_font;
};

#endif // SFFONTRENDERER_H
