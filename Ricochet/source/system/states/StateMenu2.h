#ifndef STATEMENU2_H
#define STATEMENU2_H

#include "IState.h"
#include "general.h"

#include "system/AssetManager.h"
#include "system/GameData.h"
#include "system/Settings.h"
#include "system/AudioManager.h"

#include "video/sfFontRenderer.h"
#include "video/Background.h"

struct LevelIcon
{
    sf::RectangleShape rec;//(sf::Vector2f(152,84));
    int maxOutlineThickness = 15;
    float thickness = 0;
    bool hover = false;

    void init()
    {
        rec.setOutlineColor(sf::Color(255,255,255,96));
        rec.setOutlineThickness(1);
    }

    void update()
    {
        if (hover)
        {
            if (thickness < maxOutlineThickness)
            {
                // increase size
                thickness += 200 * gdata.m_timeDelta;
                if (thickness > maxOutlineThickness) thickness = maxOutlineThickness;

                rec.setOutlineThickness(thickness);
            }
        }
        else
        {
            // decrease size
            if (thickness > 1)
            {
                thickness -= 200 * gdata.m_timeDelta;
                if (thickness < 1) thickness = 1;

                rec.setOutlineThickness(thickness);
            }
        }
    }
};

class StateMenu2 : public IState
{
    public:
        StateMenu2();
        virtual ~StateMenu2();

        virtual void load();
        virtual bool initialise();
        virtual void handleEvents();
        virtual void update();
        virtual void draw();
        virtual void freeResources();

        void mm_init();
        void om_init();
        void ls_init();

        void mm_handleEvents();
        void om_handleEvents();
        void ls_handleEvents();

        void mm_update();
        void om_update();
        void ls_update();

        void mm_draw();
        void om_draw();
        void ls_draw();

    protected:
        Camera c;
        Background background;
        sfFontRenderer     font;

        sf::Sprite title;
        int screen = 0;

    protected: // MainMenu Data
        int mm_selected = 0;
        vector<string> mm_items;

    protected: // OptionMenu Data
        void applySettings();
        void setApplied(); // sets the options in the menu to what is currently applied
        int om_selected = 0;
        sf::Sprite  next;
        sf::Sprite  prev;
        int next_state = 0;
        int prev_state = 0;
        vector<string> om_items;

        vector<string> o_res;
        bool fullscreen = true;
        bool vsync = true;
        int fps = 0;
        int sfx_vol = 100;
        int mus_vol = 100;

        int res_index = 0;

    protected: // Level Select Data
        int selected_level = 0;
        vector<LevelIcon> icons;
};

#endif // STATEMENU2_H
