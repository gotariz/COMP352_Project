#ifndef SFFONTRENDERER_H
#define SFFONTRENDERER_H

#include "sfFont.h"
#include "general.h"
#include <string>

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
        sfFontRenderer();
        virtual ~sfFontRenderer();

    public:
        void setFont(sfFont* font);
        void setColor(sf::Color c);
        void drawString(int x, int y, std::string text, int horizontalPosition = sfLib::sfAlign::LEFT, int verticalPosition = sfLib::sfAlign::TOP);
        void setWindow(sf::RenderWindow* window);

        unsigned getRenderedTextWidth(std::string text);

    private:
        sf::RenderWindow*   m_window = nullptr;
        sfFont*             m_font = nullptr;
        sf::Color           m_color = sf::Color::White;
};

#endif // SFFONTRENDERER_H
