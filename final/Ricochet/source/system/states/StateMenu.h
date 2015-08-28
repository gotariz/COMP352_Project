#ifndef STATEMENU_H
#define STATEMENU_H

#include "general.h"

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

        vector<string>  menuItems;
        int     selected = 0;

    public:

		AssetManager	    assets;

        sfFontRenderer*     font;
};

#endif // STATEMENU_H
