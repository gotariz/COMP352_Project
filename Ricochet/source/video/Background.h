#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "general.h"
#include "system/GameData.h"
#include "system/Settings.h"

class Background
{
    public:
        Vector2     position;
        int         num_circles = 0;
        sf::RectangleShape  rec;

        vector<bgCircle> circles;
        sf::Color   bubble_color;
        Vector2     bubble_alpha_range;
        void init();
        void draw();
        void update();

        void drawLine(Vector2 p1, Vector2 p2,sf::Color c);



};

#endif // BACKGROUND_H
