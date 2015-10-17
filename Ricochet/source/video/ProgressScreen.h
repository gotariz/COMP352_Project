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
        void setStars(int n);
        void update();

        float elapsed = 0;
        bool fading = true;

    protected:
        sf::Sprite starbg;
        sf::Sprite stars;
        sf::Sprite thumbs;
        sf::Sprite glow;

        Button btn_redo;
        Button btn_next;

        sfFontRenderer  txt;
};

#endif // PROGRESSSCREEN_H
