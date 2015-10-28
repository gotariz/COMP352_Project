#ifndef PROGRESSSCREEN_H
#define PROGRESSSCREEN_H

#include "general.h"
#include "system/GameData.h"
#include "system/Settings.h"
#include "system/AssetManager.h"
#include "system/AudioManager.h"
#include "sfFontRenderer.h"

class Button{
    public:
        Button(){}
        virtual ~Button(){}

        string name = "";
        int state = 0;
        bool clicked = false;
        sf::RectangleShape   rec;
        sfFontRenderer       txt;

        sf::Color c_idle;
        sf::Color c_hover;

        sf::Color b_idle;
        sf::Color b_hover;

        void init();
        void handleEvents();
        void draw();
        void setPosition(int x, int y);
        void setSize(int w, int h);
        bool isTouching(Vector2 point);
};

class ProgressScreen
{
    public:
        ProgressScreen();
        virtual ~ProgressScreen();

        void init();
        void draw();
        void handleEvents();
        void setStars(int n, int b);
        void update();

        float elapsed = 0;
        int stars = 1;
        bool fading = true;

        int one_star = 0;
        int two_star = 0;
    protected:

        int bounces = 0;

        sf::Sprite star;
        sf::Sprite glow;

        Button btn_redo;
        Button btn_next;
        Button btn_menu;

        sfFontRenderer  txt;
};

#endif // PROGRESSSCREEN_H
