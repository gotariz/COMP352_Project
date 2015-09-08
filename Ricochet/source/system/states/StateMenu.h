#ifndef STATEMENU_H
#define STATEMENU_H

#include "general.h"
#include <string>
#include <iostream>

#include "system/states/IState.h"
#include "system/AssetManager.h"
#include "system/GameData.h"
#include "system/Settings.h"
#include "system/InputHandler.h"

#include "video/sfFontRenderer.h"
#include "video/Background.h"

class StateMenu : public IState
{
    public:
        StateMenu();
        virtual ~StateMenu();

    public:
        virtual void load();
        virtual bool initialise();
        virtual void handleEvents();
        virtual void update();
        virtual void draw();
        virtual void freeResources();
        virtual void start();

        //This is the coloured rectangle around selected
        sf::RectangleShape rec;
        Background bg;

        float dur = 0.25;

        //This is a list of items in the main menu (eg. start, awards, options, exit)
        vector<string> menuItems;

        //This is a vector of all available options (vsync, fs, res, fps)
        vector<string> optionsItems;

        //This is a vector of the each vector of options (eg. a list of resolutions you can choose)
        vector<vector<string>> optionsSettings;

        //These are each selected option's choices (e.g. each resolution you can choose)
        vector<string>  vSync;
        vector<string>  fs;
        vector<string>  res;
        vector<string>  fps;

        //This is a way to track which option is selected (eg. the 3rd resolution is selected)
        vector<int>     selectedOps;

        //This is to track which main menu you are hovering
        int selected = 0;

        //This is to track which option you are hovering in the options menu
        int selectedOption = 0;

        //These are to track which setting you are hovering on a specific option
        int selectedVSync = 0;
        int selectedFs = 0;
        int selectedRes = 0;
        int selectedFPS = 0;

        //This sets the 1st state to the main menu screen
        int menuState = MENU_MAIN;

        int fsMode;
        int vSyncMode;

        void reset();

        //main menu x
        float x = 0;
        //options menu y
        int y = 0;

        //pos for x to transit to
        int tx = 0;
        //pos for x on the menu screen
        int mx = 0;

        //whether or not the menus are changing state
        bool transitioning = false;

        bool slideIn = false;

        //the menu you wish to transition to after transition animation has finished
        int pushMenu = -1;

    public:

		AssetManager	    assets;

        sfFontRenderer     font;
};

#endif // STATEMENU_H
