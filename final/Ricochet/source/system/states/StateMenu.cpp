#include "StateMenu.h"

StateMenu::StateMenu() : IState(STATE_MENU)
{
    //ctor
}

StateMenu::~StateMenu()
{
    //dtor
}

void StateMenu::load()
{
    assets.loadAssetList("data/assets.xml");
	gdata.assets = &assets;

 	gdata.window->setKeyRepeatEnabled(false);

    font = new sfFontRenderer(gdata.window);
    font->setFont(assets.getFont("purista-medium-14-white"));

	gdata.zoom = (gdata.settings->getScreenWidth() / 1920.f);

	menuItems.push_back("Start");
	menuItems.push_back("Achievements");
	menuItems.push_back("Options");
	menuItems.push_back("Exit");



	vSync.push_back(gz::toString(gdata.settings->getVsync()));
	vSync.push_back("1");
    fs.push_back(gz::toString(gdata.settings->getFullscreen()));
    fs.push_back(gz::toString(1));

    vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
	for (int i = 0; i < modes.size(); i++)
	{
	    sf::VideoMode mode = modes[i];
	    res.push_back(gz::toString(mode.width) + "x" + gz::toString(mode.height));
	}

    fps.push_back(gz::toString(gdata.settings->getFpsLimit()));
    fps.push_back(gz::toString(60));

    optionsSettings.push_back(vSync);
    optionsSettings.push_back(fs);
    optionsSettings.push_back(res);
    optionsSettings.push_back(fps);

    selectedOps.push_back(selectedVSync);
    selectedOps.push_back(selectedFs);
    selectedOps.push_back(selectedRes);
    selectedOps.push_back(selectedFPS);

	optionsItems.push_back("Vsync");
	optionsItems.push_back("Fullscreen");
	optionsItems.push_back("Resolution");
	optionsItems.push_back("FPS Limit");

    loading = false;
}

bool StateMenu::initialise()
{
    loading = true;
	load();

    return true;
}

void StateMenu::handleEvents()
{
    gdata.updateKeys();

    sf::Event event;
    while (gdata.window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            gdata.running = false;
        }

        if(menuState == MENU_MAIN)  //Handle events within the main menu screen
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                gdata.running = false;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                selected -= 1;
                if(selected < 0)
                    selected = menuItems.size() -1;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                selected += 1;
                if(selected > menuItems.size() -1)
                    selected = 0;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
            {
                if(selected == 0) //Start
                {
                    gdata.gamestate = STATE_GAME;
                }
                if(selected == 1) //Achievements
                {
                    menuState = MENU_AWARDS;
                }
                if(selected == 2) //Options
                {
                    menuState = MENU_OPTIONS;
                }
                if(selected == 3) //Exit
                {
                    gdata.running = false;
                }
            }
        }

        if(menuState == MENU_OPTIONS) //Handle events within the options menu screen
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
            {
                menuState = MENU_MAIN;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            {
                selectedOption -= 1;
                if(selectedOption < 0)
                    selectedOption = optionsItems.size() -1;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            {
                selectedOption += 1;
                if(selectedOption > optionsItems.size() -1)
                    selectedOption = 0;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            {
                selectedOps[selectedOption] += 1;
                if(selectedOps[selectedOption] > optionsSettings[selectedOption].size()-1)
                    selectedOps[selectedOption] = 0;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                selectedOps[selectedOption] -= 1;
                if(selectedOps[selectedOption] < 0 )
                    selectedOps[selectedOption] = optionsSettings[selectedOption].size()-1;
            }
        }

        if(menuState == MENU_AWARDS) //Handle events within the achievements menu screen
        {
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
            {
                menuState = MENU_MAIN;
            }
        }
    }
}

void StateMenu::update(){}

void StateMenu::draw()
{
    gdata.window->clear(sf::Color(64,64,64,255));

    font->drawString(0,0,"hello this is a test");

    // Menu animation sliding
    if(menuState == MENU_MAIN)
    {
        if( x < gdata.settings->getScreenWidth() - 200)
            x += 3.5;
    }
    else
    {
        if( x > 50)
            x -= 3.5;
    }

    y = 100;

    if(menuState == MENU_LEVELS)
    {

    }

    if(menuState == MENU_AWARDS)
    {

    }

    if(menuState == MENU_OPTIONS)
    {
        for (int i = 0; i < optionsItems.size(); i++)
        {
            if(selectedOption == i)
            {
                font->setColor(sf::Color::Cyan);
                font->drawString(gdata.settings->getScreenWidth() /2 -25, y + (50 * i), optionsItems[i]);
                font->drawString(gdata.settings->getScreenWidth() -200, y + (50 * i), optionsSettings[i][selectedOps[i]]);
            }
            else
            {
                font->setColor(sf::Color::White);
                font->drawString(gdata.settings->getScreenWidth() /2, y + (50 * i), optionsItems[i]);
                font->drawString(gdata.settings->getScreenWidth() -200, y + (50 * i), optionsSettings[i][selectedOps[i]]);
            }
        }
    }

    for(int i = 0; i < menuItems.size(); i++)
    {
        if(selected == i)
        {
            font->setColor(sf::Color::Cyan);

            // Menu Animations for selected
            if(menuState == MENU_MAIN && x > gdata.settings->getScreenWidth() - 250)
                font->drawString(x - 50, y + (100 * i), menuItems[i]);
            else if(menuState == MENU_MAIN)
                font->drawString(x,y, menuItems[i]);
            else if(x < 100)
                font->drawString(x + 50, y + (100 * i), menuItems[i]);
            else
                font->drawString(x, y + (100 * i), menuItems[i]);

        }
        else
        {
            font->setColor(sf::Color::White);
            font->drawString(x, y + (100 * i), menuItems[i]);
        }
    }

	gdata.window->display();
}

void StateMenu::freeResources(){}
void StateMenu::start(){}
