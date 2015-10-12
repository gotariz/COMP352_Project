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

        // the cemra at 0,0
        Camera c;

        // the game title image
        sf::Sprite title;

        //This is the coloured rectangle around selected
        sf::RectangleShape rec;
        Background bg;

        sf::Sprite lvlShot;
        sf::Sprite leftLvlShot;
        sf::Sprite rightLvlShot;
        sf::Sprite lbLvlShot;
        sf::Sprite rbLvlShot;

        sf::Texture lvlTex;
        sf::Texture leftLvlTex;
        sf::Texture rightLvlTex;
        sf::Texture lbLvlTex;
        sf::Texture rbLvlTex;

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
        vector<string>  mus;
        vector<string>  sfx;
        vector<string>  save;

        vector<vector<int>> world;
        vector<int> levelsInWorld;

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
        int selectedMus = 0;
        int selectedSFX = 0;
        int selectedSave = 0;
        int selectedWorld = 0;

        //This sets the 1st state to the main menu screen
        int menuState = MENU_MAIN;

        int fsMode;
        int vSyncMode;

        //Resets display settings
        void reset();

        //Refresh the level select tile textures
        void refreshTextures();

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

        //count the levels for level select
        int levelCount = 0;
        int selectedLevel = 0;
        int leftLevel = 0;
        int rightLevel = 1;
        int lbLevel = 0;
        int rbLevel = 0;

        //center, left and right x for level screenshots
        float cx = 0;
        float lx = 0;
        float olx = 0;
        float rx = 0;
        float orx = 0;

        //center y for level screenshots
        float cy = 0;

        bool slideLeft = false;
        bool slideRight = false;

        bool locked = false;

    public:

		AssetManager	    assets;

        sfFontRenderer     font;
};

#endif // STATEMENU_H
