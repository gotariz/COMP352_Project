#ifndef SDLFONTRENDERER_H
#define SDLFONTRENDERER_H

#include <string>
#include "sdl.h"

#include "sdlFont.h"
#include "enums.h"

class sdlFontRenderer
{
    public:
        sdlFontRenderer(SDL_Renderer* renderer);
        virtual ~sdlFontRenderer();

    public:
        void setFont(sdlFont* font);
        void drawString(int x, int y, std::string text, int horizontalPosition = LEFT, int verticalPosition = TOP);

        unsigned getRenderedTextWidth(std::string text);

    private:
        SDL_Renderer*	m_renderer;
        sdlFont*		m_font;
};

#endif // SDLFONTRENDERER_H
