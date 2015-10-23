#ifndef ACHIEVEMENTBAR_H
#define ACHIEVEMENTBAR_H

#include "general.h"
#include "system/GameData.h"
#include "system/AssetManager.h"
#include "sfFontRenderer.h"
#include "system/AudioManager.h"

class AchievementBar
{
    public:
        AchievementBar();
        virtual ~AchievementBar();

        void draw(int x, int y);
        void update();
        void init();
        void setText(string description);

        sf::Color c_box;
        float age = 0;

    protected:
        string text = "";
        float elapsed_time = 0;
        float dir = 1;
        float dur = 0.5;


        sf::RectangleShape  box;
        sf::Sprite          trophey;
        sf::Sprite          glow;
        sfFontRenderer      renderer;

};

#endif // ACHIEVEMENTBAR_H
