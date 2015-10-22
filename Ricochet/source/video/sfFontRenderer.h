#ifndef SFFONTRENDERER_H
#define SFFONTRENDERER_H

#include "sfFont.h"
#include "general.h"
#include <string>

class sfFontRenderer
{
    public:
        sfFontRenderer();
        virtual ~sfFontRenderer();

    public:
        void setFont(sfFont* font);
        void setColor(sf::Color c);
        void drawString(int x, int y, std::string text, int horizontalPosition = Align::LEFT, int verticalPosition = Align::TOP);
        void setWindow(sf::RenderWindow* window);

        unsigned getRenderedTextWidth(std::string text);

        void setRotation(float rotation);
        float getRotation();

        void setTransparency(float transparency);
        float getTransparency();

    private:
        sf::RenderWindow*   m_window = nullptr;
        sfFont*             m_font = nullptr;
        sf::Color           m_color = sf::Color::White;
        float               m_transparency = 255;
        float               m_rotation = 0;
};

#endif // SFFONTRENDERER_H
