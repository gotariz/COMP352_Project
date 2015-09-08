#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "general.h"
#include "system/GameData.h"

class Background
{
    public:
        Vector2     position;
        sf::Sprite  bg_image;
        int         num_circles = 0;

        vector<bgCircle> circles;
        sf::Color bubble_color;
        Vector2     bubble_alpha_range;
        void init();
        void draw();
        void update();

};

#endif // BACKGROUND_H
