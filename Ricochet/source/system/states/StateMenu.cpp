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
    font.setWindow(gdata.window);
    font.setFont(gdata.assets->getFont("purista-medium-14-white"));

	menuItems.push_back("Start");
	menuItems.push_back("Achievements");
	menuItems.push_back("Options");
	menuItems.push_back("Exit");

    fsMode = gdata.settings->getFullscreen();
    vSyncMode = gdata.settings->getVsync();

	vSync.push_back("Off");
	vSync.push_back("On");
    fs.push_back("Windowed");
    fs.push_back("Fullscreen");

    vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
	for (int i = 0; i < modes.size(); i++)
	{
	    sf::VideoMode mode = modes[i];
	    res.push_back(gz::toString(mode.width) + "x" + gz::toString(mode.height));

	    if(mode.width == gdata.settings->getScreenWidth() && mode.height == gdata.settings->getScreenHeight())
        {
            selectedRes = i;
            cout << "selectedRes = " << i << endl;
        }
	}

	selectedVSync   = gdata.settings->getVsync();
	selectedFs      = gdata.settings->getFullscreen();
	selectedFPS     = gdata.settings->getFpsLimit();

    cout << "\n<----------------------SETTINGS LOADED-------------------------->\n"
         << "\tvSync:\t\t\t\t" << selectedVSync << "\n"
         << "\tFullscreen:\t\t\t" << selectedFs << "\n"
         << "\tResolution:\t\t\t" << gdata.settings->getScreenWidth() << "x"
         << gdata.settings->getScreenHeight() << "\n"
         << "\tFPS Limit:\t\t\t" << selectedFPS << endl;


    fps.push_back(gz::toString(0));
    fps.push_back(gz::toString(60));

    optionsSettings.push_back(vSync);
    optionsSettings.push_back(fs);
    optionsSettings.push_back(res);
    optionsSettings.push_back(fps);

    selectedVSync   = gdata.settings->getVsync();
    selectedFs      = gdata.settings->getFullscreen();
    selectedFPS     = gdata.settings->getFpsLimit();

    selectedOps.push_back(selectedVSync);
    selectedOps.push_back(selectedFs);
    selectedOps.push_back(selectedRes);
    selectedOps.push_back(selectedFPS);

	optionsItems.push_back("Vsync");
	optionsItems.push_back("Fullscreen");
	optionsItems.push_back("Resolution");
	optionsItems.push_back("FPS Limit");

    bg.bg_image.setTexture(*gdata.assets->getTexture("background"));
    bg.bg_image.setColor(sf::Color(6,23,40,255));
	bg.num_circles = 100;
	bg.init();

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

        else if(gdata.keys[sf::Keyboard::R].isKeyPressed)
        {
            if(event.key.code == sf::Keyboard::R)
            {
                reset();
            }
        }
    }

    if(menuState == MENU_MAIN)  //Handle events within the main menu screen
    {
        if(gdata.keys[sf::Keyboard:: Escape].isKeyPressed)
        {
            gdata.running = false;
        }

        else if (gdata.keys[sf::Keyboard::Up].isKeyPressed)
        {
            selected -= 1;
            if(selected < 0)
                selected = menuItems.size() -1;
        }

        else if (gdata.keys[sf::Keyboard::Down].isKeyPressed)
        {
            selected += 1;
            if(selected > menuItems.size() -1)
                selected = 0;
        }

        else if (gdata.keys[sf::Keyboard::Return].isKeyPressed)
        {
            if(selected == 0) //Start
            {
                gdata.gamestate = STATE_GAME;
                if(event.key.code == sf::Keyboard::Escape)
                {
                    gdata.running = false;
                }

                else if (event.key.code == sf::Keyboard::Up)
                {
                    selected -= 1;
                    if(selected < 0)
                        selected = menuItems.size() -1;
                }

                else if (event.key.code == sf::Keyboard::Down)
                {
                    selected += 1;
                    if(selected > menuItems.size() -1)
                        selected = 0;
                }

                else if(event.key.code == sf::Keyboard::Return)
                {
                    if(selected == 0) //Start
                    {
                        gdata.gamestate = STATE_GAME;
                    }
                    else if(selected == 1) //Achievements
                    {
                        menuState = MENU_AWARDS;
                    }
                    else if(selected == 2) //Options
                    {
                        menuState = MENU_OPTIONS;
                    }
                    else if(selected == 3) //Exit
                    {
                        gdata.running = false;
                    }
                }
            }
            else if(selected == 1) //Achievements
            {
                //menuState = MENU_AWARDS;
                if(event.key.code == sf::Keyboard::BackSpace)
                {
                    menuState = MENU_MAIN;
                }

            }
            else if(selected == 2) //Options
            {
                menuState = MENU_OPTIONS;
            }
            else if(selected == 3) //Exit
            {
                gdata.running = false;
                if(event.key.code == sf::Keyboard::BackSpace)
                {
                    menuState = MENU_MAIN;
                }
            }
        }
    }

    else if(menuState == MENU_OPTIONS) //Handle events within the options menu screen
    {
        if(gdata.keys[sf::Keyboard::BackSpace].isKeyPressed)
        {
            menuState = MENU_MAIN;
        }


        else if (gdata.keys[sf::Keyboard::Return].isKeyPressed)
        {
            vSyncMode = selectedOps[0];
            selectedFs = selectedOps[1];

            gdata.settings->setVsync(vSyncMode);
            gdata.settings->setFullscreen(selectedFs);

            gdata.settings->setScreenWidth(gz::stringToUnsigned(gz::splitString(optionsSettings[2][selectedRes], 'x')[0]));
            gdata.settings->setScreenHeight(gz::stringToUnsigned(gz::splitString(optionsSettings[2][selectedRes], 'x')[1]));

            gdata.settings->setFpsLimit(gz::stringToUnsigned(optionsSettings[3][selectedFPS]));

            gdata.settings->saveSettings();

            gdata.window->setSize(sf::Vector2u(gdata.settings->getScreenWidth(),gdata.settings->getScreenHeight()));
            gdata.view = new sf::View(sf::FloatRect(0,0,gdata.settings->getScreenWidth(),gdata.settings->getScreenHeight()));
            gdata.window->setView(*gdata.view);
            gdata.window->setFramerateLimit(gdata.settings->getFpsLimit());
            gdata.window->setVerticalSyncEnabled(vSyncMode);

//            if(selectedFs != gdata.settings->getFullscreen())
//            {
//                gdata.window->close();
//                gdata.window->
//            }
//
            cout << "\n<----------------------SETTINGS SAVED-------------------------->\n"
                 << "\tvSync:\t\t\t\t" << vSyncMode << "\n"
                 << "\tFullscreen:\t\t\t" << selectedFs << "\n"
                 << "\tResolution:\t\t\t" << gz::splitString(optionsSettings[2][selectedRes], 'x')[0] << "x"
                 << gz::splitString(optionsSettings[2][selectedRes], 'x')[1] << "\n"
                 << "\tFPS Limit:\t\t\t" << gz::stringToUnsigned(optionsSettings[3][selectedFPS]) << endl;

            //gdata.window->setPosition(sf::Vector2i(0,0));
            //menuState = MENU_MAIN;
        }

        else if (gdata.keys[sf::Keyboard::Up].isKeyPressed)
        {
            selectedOption -= 1;
            if(selectedOption < 0)
                selectedOption = optionsItems.size() -1;
        }

        else if (gdata.keys[sf::Keyboard::Down].isKeyPressed)
        {
            selectedOption += 1;
            if(selectedOption > optionsItems.size() -1)
                selectedOption = 0;
        }

        else if (gdata.keys[sf::Keyboard::Right].isKeyPressed)
        {
            selectedOps[selectedOption] += 1;
            if(selectedOps[selectedOption] > optionsSettings[selectedOption].size()-1)
                selectedOps[selectedOption] = 0;

            if(selectedOption == 0)
                selectedVSync = selectedOps[selectedOption];
            else if(selectedOption == 1)
                selectedFs = selectedOps[selectedOption];
            else if(selectedOption == 2)
                selectedRes = selectedOps[selectedOption];
            else if(selectedOption == 3)
                selectedFPS = selectedOps[selectedOption];
        }

        else if (gdata.keys[sf::Keyboard::Left].isKeyPressed)
        {
            selectedOps[selectedOption] -= 1;
            if(selectedOps[selectedOption] < 0 )
                selectedOps[selectedOption] = optionsSettings[selectedOption].size()-1;

            if(selectedOption == 0)
                selectedVSync = selectedOps[selectedOption];
            else if(selectedOption == 1)
                selectedFs = selectedOps[selectedOption];
            else if(selectedOption == 2)
                selectedRes = selectedOps[selectedOption];
            else if(selectedOption == 3)
                selectedFPS = selectedOps[selectedOption];
        }
    }
    else if(menuState == MENU_AWARDS) //Handle events within the achievements menu screen
    {
        if(gdata.keys[sf::Keyboard::BackSpace].isKeyPressed)
        {
            menuState = MENU_MAIN;
        }
    }
}

void StateMenu::reset()
{
    gdata.settings->setScreenWidth(600);
    gdata.settings->setScreenHeight(400);

    gdata.settings->saveSettings();

    // this is important to stop memory leaks
    if (gdata.view != nullptr)
    {
        gdata.view = nullptr;
    }

    gdata.window->setSize(sf::Vector2u(gdata.settings->getScreenWidth(),gdata.settings->getScreenHeight()));
    gdata.view = new sf::View(sf::FloatRect(0,0,gdata.settings->getScreenWidth(),gdata.settings->getScreenHeight()));
    gdata.window->setView(*gdata.view);
    gdata.window->setFramerateLimit(gdata.settings->getFpsLimit());
}

void StateMenu::update()
{
    bg.update();
}

void StateMenu::draw()
{
    gdata.window->clear(sf::Color(64,64,64,255));
    bg.draw();
    font.drawString(0,0,"Press 'R' to reset screen");

    // Menu animation sliding;
    if(menuState == MENU_MAIN)
    {
        if( x < gdata.settings->getScreenWidth() - 200)
            x += (gdata.settings->getScreenWidth() - 200) * gdata.m_timeDelta;//gdata.settings->getScreenWidth()*0.003;
    }
    else
    {
        if( x > 50)
            x -= (gdata.settings->getScreenWidth() - 200) * gdata.m_timeDelta;//gdata.settings->getScreenWidth()*0.003;
    }

    y = gdata.settings->getScreenHeight()/5;

    if(menuState == MENU_LEVELS)
    {

    }

    if(menuState == MENU_AWARDS)
    {

    }

    if(menuState == MENU_OPTIONS) //! NEED ANIMATIONS
    {
        for (int i = 0; i < optionsItems.size(); i++)
        {
            if(selectedOption == i)
            {
                font.setColor(sf::Color::Cyan);
                font.drawString(gdata.settings->getScreenWidth() /2 -25, y + (gdata.settings->getScreenHeight()/10 * i), optionsItems[i]);
                font.drawString(gdata.settings->getScreenWidth() -200, y + (gdata.settings->getScreenHeight()/10 * i), optionsSettings[i][selectedOps[i]]);
            }
            else
            {
                font.setColor(sf::Color::White);
                font.drawString(gdata.settings->getScreenWidth() /2, y + (gdata.settings->getScreenHeight()/10 * i), optionsItems[i]);
                font.drawString(gdata.settings->getScreenWidth() -200, y + (gdata.settings->getScreenHeight()/10 * i), optionsSettings[i][selectedOps[i]]);
            }
        }
    }

    for(int i = 0; i < menuItems.size(); i++)
    {
        if(selected == i)
        {
            font.setColor(sf::Color::Cyan);

            // Menu Animations for selected
            if(menuState == MENU_MAIN && x > gdata.settings->getScreenWidth() - 250)
                font.drawString(x - 50, y + (gdata.settings->getScreenHeight()/10 * i), menuItems[i]);
            else if(menuState == MENU_MAIN)
                font.drawString(x,y + (gdata.settings->getScreenHeight()/10 * i), menuItems[i]);
            else if(x < 100)
                font.drawString(x + 50, y + (gdata.settings->getScreenHeight()/10 * i), menuItems[i]);
            else
                font.drawString(x, y + (gdata.settings->getScreenHeight()/10 * i), menuItems[i]);

        }
        else
        {
            font.setColor(sf::Color::White);
            font.drawString(x, y + (gdata.settings->getScreenHeight()/10 * i), menuItems[i]);
        }
    }

	gdata.window->display();
}

void StateMenu::freeResources(){}
void StateMenu::start(){}
