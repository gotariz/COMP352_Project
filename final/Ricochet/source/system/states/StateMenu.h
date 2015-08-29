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

        vector<string> menuItems;
        vector<string> optionsItems;
        vector<vector<string>> optionsSettings;

        vector<string>  vSync;
        vector<string>  fs;
        vector<string>  res;
        vector<string>  fps;
        vector<int>     selectedOps;

        int selected = 0;
        int selectedOption = 0;
        int selectedVSync = 0;
        int selectedFs = 0;
        int selectedRes = 0;
        int selectedFPS = 0;
        int menuState = MENU_MAIN;

        float x;
        float y;

    public:

		AssetManager	    assets;

        sfFontRenderer*     font;
};

#endif // STATEMENU_H
