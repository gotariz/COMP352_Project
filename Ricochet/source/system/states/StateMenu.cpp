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

    gdata.camera = &c;
    //bg.bg_image.setTexture(*gdata.assets->getTexture("background"));
    bg.bubble_alpha_range.set(0,64);
    bg.bubble_color = sf::Color(0,0,0,255);
	bg.num_circles = 60;
	bg.init();

    //font = new sfFontRenderer(gdata.window);
    font.setWindow(gdata.window);
    font.setFont(assets.getFont("segoe-ui-light-48"));

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
    save.push_back("Accept");
    save.push_back("Cancel");
    save.push_back("Default");

    for (int i = 0; i < 11; i++)
    {
        mus.push_back(gz::toString(i*10));
    }

    for (int i = 0; i < 11; i++)
    {
        sfx.push_back(gz::toString(i*10));
    }

    vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
	for (int i = 0; i < modes.size(); i++)
	{
	    sf::VideoMode mode = modes[i];
	    res.push_back(gz::toString(mode.width) + "x" + gz::toString(mode.height));

	    if(mode.width == gdata.settings->getScreenWidth() && mode.height == gdata.settings->getScreenHeight())
        {
            selectedRes = (modes.size() - 1) - i;
            cout << "selectedRes = " << i << endl;
        }
	}
	reverse(res.begin(),res.end());

	selectedVSync   = gdata.settings->getVsync();
	selectedFs      = gdata.settings->getFullscreen();
	selectedFPS     = gdata.settings->getFpsLimit();
    selectedMus     = gdata.settings->getVolume()/10;
    selectedSFX     = gdata.settings->getSFX()/10;
    selectedSave    = 0;

	//HARD CODED FPS FIX
	if(selectedFPS == 60)
	{
        selectedFPS = 1;
        cout << "FPS Fixed" << endl;
	}
	if(selectedFPS == 120)
	{
        selectedFPS = 2;
        cout << "FPS Fixed" << endl;
	}

    cout << "\n<----------------------SETTINGS LOADED-------------------------->\n"
         << "\tvSync:\t\t\t\t" << selectedVSync << "\n"
         << "\tFullscreen:\t\t\t" << selectedFs << "\n"
         << "\tResolution:\t\t\t" << gdata.settings->getScreenWidth() << "x"
         << gdata.settings->getScreenHeight() << "\n"
         << "\tFPS Limit:\t\t\t" << selectedFPS << endl;


    fps.push_back(gz::toString(0));
    fps.push_back(gz::toString(60));
    fps.push_back(gz::toString(120));

    optionsSettings.push_back(vSync);
    optionsSettings.push_back(fs);
    optionsSettings.push_back(res);
    optionsSettings.push_back(fps);
    optionsSettings.push_back(mus);
    optionsSettings.push_back(sfx);
    optionsSettings.push_back(save);

    selectedOps.push_back(selectedVSync);
    selectedOps.push_back(selectedFs);
    selectedOps.push_back(selectedRes);
    selectedOps.push_back(selectedFPS);
    selectedOps.push_back(selectedMus);
    selectedOps.push_back(selectedSFX);
    selectedOps.push_back(selectedSave);

	optionsItems.push_back("Vsync");
	optionsItems.push_back("Fullscreen");
	optionsItems.push_back("Resolution");
	optionsItems.push_back("FPS Limit");
	optionsItems.push_back("Volume");
	optionsItems.push_back("Sound Effects");
	optionsItems.push_back("Save Settings");

    //count the amount of levels in the XML
	while(true)
    {
        if(utils::fexists(gz::toString(LEVEL_PATH + gz::toString(levelCount) + ".xml")))
        {
            levelCount += 1;
        }
        else
        {
            levelCount -= 1;
            levelCount += 3;
            break;
        }
    }

	cout << "Level count: " << levelCount << endl;

	leftLevel = levelCount;

    mx = gdata.settings->getScreenWidth() - 400;
    tx = gdata.settings->getScreenWidth() + 10;
    y = gdata.settings->getScreenHeight() - 40 - (78 * 4);
    x = mx;

    lvlShot.setTexture(*gdata.assets->getTexture("Screencap_Level_"+gz::toString(selectedLevel)));
    leftLvlShot.setTexture(*gdata.assets->getTexture("Screencap_Level_"+gz::toString(leftLevel)));
    rightLvlShot.setTexture(*gdata.assets->getTexture("Screencap_Level_"+gz::toString(rightLevel)));
    lbLvlShot.setTexture(*gdata.assets->getTexture("Screencap_Level_"+gz::toString(lbLevel)));
    rbLvlShot.setTexture(*gdata.assets->getTexture("Screencap_Level_"+gz::toString(rbLevel)));

    cx = gdata.settings->getScreenWidth()/2;
    rx = gdata.settings->getScreenWidth() - (rightLvlShot.getTexture()->getSize().x/5) - 20;
    lx = 0 + (leftLvlShot.getTexture()->getSize().x/5) + 20;
    cy = gdata.settings->getScreenHeight()/2;
    olx = 0;
    orx = gdata.settings->getScreenWidth();

    lvlShot.setPosition(cx, cy);
    lvlShot.setScale(0.5,0.5);
    lvlShot.setOrigin(lvlShot.getTexture()->getSize().x / 2, lvlShot.getTexture()->getSize().y / 2);

    leftLvlShot.setScale(0.2,0.2);
    leftLvlShot.setPosition(lx, cy);
    leftLvlShot.setColor(sf::Color(150,150,150,200));
    leftLvlShot.setOrigin(leftLvlShot.getTexture()->getSize().x / 2, leftLvlShot.getTexture()->getSize().y / 2);

    rightLvlShot.setPosition(rx, cy);
    rightLvlShot.setScale(0.2,0.2);
    rightLvlShot.setColor(sf::Color(150,150,150,200));
    rightLvlShot.setOrigin(rightLvlShot.getTexture()->getSize().x / 2, rightLvlShot.getTexture()->getSize().y / 2);

    rbLvlShot.setPosition(orx, cy);
    rbLvlShot.setScale(0.1,0.1);
    rbLvlShot.setColor(sf::Color(100,100,100,100));
    rbLvlShot.setOrigin(rbLvlShot.getTexture()->getSize().x / 2, rbLvlShot.getTexture()->getSize().y / 2);

    lbLvlShot.setPosition(olx, cy);
    lbLvlShot.setScale(0.1,0.1);
    lbLvlShot.setColor(sf::Color(100,100,100,100));
    lbLvlShot.setOrigin(lbLvlShot.getTexture()->getSize().x / 2, lbLvlShot.getTexture()->getSize().y / 2);

//    int rMus = utils::getRandom(0,3);
    int rMus = 2;
    cout << "RMUS: " << rMus << endl;

    music.stop();
    music.setLoop(true);
    if(rMus == 1)
        music.openFromFile(gdata.assets->getMusic("music1"));
    if(rMus == 2)
        music.openFromFile(gdata.assets->getMusic("music2"));
    if(rMus == 3)
        music.openFromFile(gdata.assets->getMusic("music3"));
    music.setVolume(gdata.settings->getVolume());
    music.play();

    title.setTexture(*gdata.assets->getTexture("title"));
    title.setOrigin(title.getTexture()->getSize().x/2,title.getTexture()->getSize().y/2);
    title.setPosition(gdata.settings->getScreenWidth()/2,150);


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
    }

    //general keys for all menu
    if(gdata.keys[sf::Keyboard:: Escape].isKeyPressed)
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

    //specific keys for each sub-menu
    if(!transitioning)
    {
        if(menuState == MENU_MAIN)  //Handle events within the main menu screen
        {
            if (gdata.keys[sf::Keyboard::Up].isKeyPressed)
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


            else if(event.key.code == sf::Keyboard::Return)
            {
                if(selected == 0) //Start
                {
//                    gdata.gamestate = STATE_GAME;
                    transitioning = true;
                    pushMenu = MENU_LEVELS;
                }
                else if(selected == 1) //Achievements
                {
                    transitioning = true;
                    pushMenu = MENU_AWARDS;
                }
                else if(selected == 2) //Options
                {
                    transitioning = true;
                    pushMenu = MENU_OPTIONS;
                }
                else if(selected == 3) //Exit
                {
                    gdata.running = false;
                }
            }
        }

        else if(menuState == MENU_OPTIONS) //Handle events within the options menu screen
        {
            if(gdata.keys[sf::Keyboard::BackSpace].isKeyPressed)
            {
                transitioning = true;
                pushMenu = MENU_MAIN;
            }


            else if (gdata.keys[sf::Keyboard::Return].isKeyPressed)
            {
                if(selectedOption == 6 && selectedSave == 0)//save
                {
                    vSyncMode = selectedOps[0];
                    selectedFs = selectedOps[1];

                    gdata.settings->setVsync(vSyncMode);
                    gdata.settings->setFullscreen(selectedFs);

                    //reset window position
                    if((gz::stringToUnsigned(gz::splitString(optionsSettings[2][selectedRes], 'x')[0]) != gdata.settings->getScreenWidth())
                       || gz::stringToUnsigned(gz::splitString(optionsSettings[2][selectedRes], 'x')[1]) != gdata.settings->getScreenHeight())
                        gdata.window->setPosition(sf::Vector2i(0,0));

                    gdata.settings->setScreenWidth(gz::stringToUnsigned(gz::splitString(optionsSettings[2][selectedRes], 'x')[0]));
                    gdata.settings->setScreenHeight(gz::stringToUnsigned(gz::splitString(optionsSettings[2][selectedRes], 'x')[1]));
                    gdata.settings->setFpsLimit(gz::stringToUnsigned(optionsSettings[3][selectedFPS]));

                    gdata.settings->setVolume(gz::stringToUnsigned(optionsSettings[4][selectedMus]));
                    gdata.settings->setSFX(gz::stringToUnsigned(optionsSettings[5][selectedSFX]));

                    gdata.settings->saveSettings();

                    gdata.window->setSize(sf::Vector2u(gdata.settings->getScreenWidth(),gdata.settings->getScreenHeight()));
                    gdata.view = new sf::View(sf::FloatRect(0,0,gdata.settings->getScreenWidth(),gdata.settings->getScreenHeight()));
                    gdata.window->setView(*gdata.view);
                    gdata.window->setFramerateLimit(gdata.settings->getFpsLimit());
                    gdata.window->setVerticalSyncEnabled(vSyncMode);

                    music.setVolume(gdata.settings->getVolume());

                    cout << "\n<----------------------SETTINGS SAVED-------------------------->\n"
                         << "\tvSync:\t\t\t\t" << vSyncMode << "\n"
                         << "\tFullscreen:\t\t\t" << selectedFs << "\n"
                         << "\tResolution:\t\t\t" << gz::splitString(optionsSettings[2][selectedRes], 'x')[0] << "x"
                         << gz::splitString(optionsSettings[2][selectedRes], 'x')[1] << "\n"
                         << "\tFPS Limit:\t\t\t" << gz::stringToUnsigned(optionsSettings[3][selectedFPS]) << "\n"
                         << "\tVolume:\t\t\t\t" << gz::stringToUnsigned(optionsSettings[4][selectedMus]) << "\n"
                         << "\tSFX:\t\t\t\t" << gz::stringToUnsigned(optionsSettings[4][selectedSFX]) << endl;

                    mx = gdata.settings->getScreenWidth() - 400;
                    tx = gdata.settings->getScreenWidth() + 10;
                    y = gdata.settings->getScreenHeight() - 40 - (78 * 4);
                    x = mx;

                    cx = gdata.settings->getScreenWidth()/2;
                    rx = gdata.settings->getScreenWidth() - (rightLvlShot.getTexture()->getSize().x/5) - 20;
                    lx = 0 + (leftLvlShot.getTexture()->getSize().x/5) + 20;
                    cy = gdata.settings->getScreenHeight()/2;
                    olx = 0;
                    orx = gdata.settings->getScreenWidth();
                    transitioning = true;
                    pushMenu = MENU_MAIN;
                }
                else if(selectedOption == 6 && selectedSave == 1) //cancel
                {
                    transitioning = true;
                    pushMenu = MENU_MAIN;
                }
                else if(selectedOption == 6 && selectedSave == 2) //default
                {
                    reset();
                    transitioning = true;
                    pushMenu = MENU_MAIN;
                }
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
                else if(selectedOption == 4)
                    selectedMus = selectedOps[selectedOption];
                else if(selectedOption == 5)
                    selectedSFX = selectedOps[selectedOption];
                else if(selectedOption == 6)
                    selectedSave = selectedOps[selectedOption];
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
                else if(selectedOption == 4)
                    selectedMus = selectedOps[selectedOption];
                else if(selectedOption == 5)
                    selectedSFX = selectedOps[selectedOption];
                else if(selectedOption == 6)
                    selectedSave = selectedOps[selectedOption];
            }
        }

        else if(menuState == MENU_AWARDS) //Handle events within the achievements menu screen
        {
            if(gdata.keys[sf::Keyboard::BackSpace].isKeyPressed)
            {
//                menuState = MENU_MAIN;
                transitioning = true;
                pushMenu = MENU_MAIN;
            }
        }

        else if(menuState == MENU_LEVELS) //Handle events within the level select menu screen
        {
            if(gdata.keys[sf::Keyboard::BackSpace].isKeyPressed)
            {
                transitioning = true;
                pushMenu = MENU_MAIN;
            }

            else if (gdata.keys[sf::Keyboard::Right].isKeyPressed)
            {
                if(!slideLeft && !slideRight)
                    slideLeft = true;
            }

            else if (gdata.keys[sf::Keyboard::Left].isKeyPressed)
            {
                if(!slideLeft && !slideRight)
                    slideRight = true;
            }

            else if (gdata.keys[sf::Keyboard::Return].isKeyPressed)
            {
                if(!locked)
                {
                    gdata.level = selectedLevel;
                    gdata.gamestate = STATE_GAME;
                    music.stop();
                }
            }

            else if (gdata.keys[sf::Keyboard::Space].isKeyPressed)
            {
//               cout << "lx:" << lx + ((leftLvlShot.getSize().x * leftLvlShot.getScale().x) /2)
//                    << " cx:" << cx
//                    << " rx:" << rx - ((rightLvlShot.getSize().x * rightLvlShot.getScale().x) /2) << endl;
            }
        }
    }
}

void StateMenu::reset()
{
    gdata.settings->setScreenWidth(1920);
    gdata.settings->setScreenHeight(1080);
    gdata.settings->setFullscreen(false);
    gdata.settings->setFpsLimit(0);
    gdata.settings->setSFX(100);
    gdata.settings->setVolume(100);
    gdata.settings->setVsync(0);


    gdata.settings->saveSettings();

    vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
	for (int i = 0; i < modes.size(); i++)
	{
	    sf::VideoMode mode = modes[i];
	    if(mode.width == gdata.settings->getScreenWidth() && mode.height == gdata.settings->getScreenHeight())
        {
            selectedRes = (modes.size() - 1) - i;
            cout << "selectedRes = " << i << endl;
        }
	}
    selectedOps[0] = 0;
	selectedOps[1] = 0;
	selectedOps[2] = selectedRes;
	selectedOps[3] = 0;
	selectedOps[4] = 10;
	selectedOps[5] = 10;

    gdata.window->setSize(sf::Vector2u(gdata.settings->getScreenWidth(),gdata.settings->getScreenHeight()));
    gdata.view = new sf::View(sf::FloatRect(0,0,gdata.settings->getScreenWidth(),gdata.settings->getScreenHeight()));
    gdata.window->setView(*gdata.view);
    gdata.window->setFramerateLimit(gdata.settings->getFpsLimit());
}

void StateMenu::update()
{
    bg.update();
    if(selectedLevel == levelCount - 1 || selectedLevel == levelCount - 2 || selectedLevel == levelCount)
        locked = true;
    else
        locked = false;

    //Correct position from the bottom of screen
    vector<string> vec;
    if (menuState == MENU_MAIN)
        vec = menuItems;
    else if (menuState == MENU_OPTIONS)
        vec = optionsItems;

    mx = gdata.settings->getScreenWidth() - 400;
    tx = gdata.settings->getScreenWidth() + 10;
    y = gdata.settings->getScreenHeight() - 40 - (78 * vec.size());
//    olx = 0;
//    orx = gdata.settings->getScreenWidth();
//    lx = 20;

    // Menu animation sliding;
    if(transitioning)
    {
        if (slideIn)
        {
            x -= (tx - mx) * (gdata.m_timeDelta * (1/dur));
            if (x < mx)
            {
                slideIn = false;
                transitioning = false;
                x = mx;
            }
//            if(menuState == MENU_LEVELS)
//            {
//                if(lvlShot.getColor().r < 255 )
//                    lvlShot.setColor(sf::Color(lvlShot.getColor().r + (255)*(gdata.m_timeDelta * (1/dur)),
//                                               lvlShot.getColor().g + (255)*(gdata.m_timeDelta * (1/dur)),
//                                               lvlShot.getColor().b + (255)*(gdata.m_timeDelta * (1/dur)),
//                                               lvlShot.getColor().a + (255)*(gdata.m_timeDelta * (1/dur))));
//                else
//                    lvlShot.setColor(sf::Color(255,255,255,255));
//                if(rightLvlShot.getColor().r < 150 )
//                    rightLvlShot.setColor(sf::Color(rightLvlShot.getColor().r + (150)*(gdata.m_timeDelta * (1/dur)),
//                                                    rightLvlShot.getColor().g + (150)*(gdata.m_timeDelta * (1/dur)),
//                                                    rightLvlShot.getColor().b + (150)*(gdata.m_timeDelta * (1/dur)),
//                                                    rightLvlShot.getColor().a + (200)*(gdata.m_timeDelta * (1/dur))));
//                else
//                    rightLvlShot.setColor(sf::Color(150,150,150,200));
//                if(leftLvlShot.getColor().r < 150 )
//                    leftLvlShot.setColor(sf::Color(leftLvlShot.getColor().r + (150)*(gdata.m_timeDelta * (1/dur)),
//                                                   leftLvlShot.getColor().g + (150)*(gdata.m_timeDelta * (1/dur)),
//                                                   leftLvlShot.getColor().b + (150)*(gdata.m_timeDelta * (1/dur)),
//                                                   leftLvlShot.getColor().a + (200)*(gdata.m_timeDelta * (1/dur))));
//                else
//                    leftLvlShot.setColor(sf::Color(150,150,150,200));
//            }
        }
        else if (!slideIn)
        {
            x += (tx - mx) * (gdata.m_timeDelta * (1/dur));
            if (x > tx)
            {
                slideIn = true;
                menuState = pushMenu;
                x = tx;
            }
//            if(menuState == MENU_LEVELS)
//            {
//                if(lvlShot.getColor().r > 0 )
//                    lvlShot.setColor(sf::Color(lvlShot.getColor().r - (255)*(gdata.m_timeDelta * (1/dur)),
//                                               lvlShot.getColor().g - (255)*(gdata.m_timeDelta * (1/dur)),
//                                               lvlShot.getColor().b - (255)*(gdata.m_timeDelta * (1/dur)),
//                                               lvlShot.getColor().a - (255)*(gdata.m_timeDelta * (1/dur))));
//                else
//                    lvlShot.setColor(sf::Color(0,0,0,0));
//                if(rightLvlShot.getColor().r > 0 )
//                    rightLvlShot.setColor(sf::Color(rightLvlShot.getColor().r - (150)*(gdata.m_timeDelta * (1/dur)),
//                                                    rightLvlShot.getColor().g - (150)*(gdata.m_timeDelta * (1/dur)),
//                                                    rightLvlShot.getColor().b - (150)*(gdata.m_timeDelta * (1/dur)),
//                                                    rightLvlShot.getColor().a - (200)*(gdata.m_timeDelta * (1/dur))));
//                else
//                    rightLvlShot.setColor(sf::Color(0,0,0,0));
//                if(leftLvlShot.getColor().r > 0 )
//                    leftLvlShot.setColor(sf::Color(leftLvlShot.getColor().r - (150)*(gdata.m_timeDelta * (1/dur)),
//                                                   leftLvlShot.getColor().g - (150)*(gdata.m_timeDelta * (1/dur)),
//                                                   leftLvlShot.getColor().b - (150)*(gdata.m_timeDelta * (1/dur)),
//                                                   leftLvlShot.getColor().a - (200)*(gdata.m_timeDelta * (1/dur))));
//                else
//                    leftLvlShot.setColor(sf::Color(0,0,0,0));
//            }
        }
    }

    if(slideLeft)
    {
        //MOVE cx to the lx
        if(lvlShot.getPosition().x > lx )
            lvlShot.setPosition(lvlShot.getPosition().x - (cx - lx) *(gdata.m_timeDelta * (1/dur)), cy);
        if(lvlShot.getScale().x > 0.2)
            lvlShot.setScale(lvlShot.getScale().x - ((0.5-0.2)*(gdata.m_timeDelta * (1/dur))),
                             lvlShot.getScale().y - ((0.5-0.2)*(gdata.m_timeDelta * (1/dur))));
        if(lvlShot.getColor().r > 150 )
            lvlShot.setColor(sf::Color(lvlShot.getColor().r - (255-150)*(gdata.m_timeDelta * (1/dur)),
                                           lvlShot.getColor().g - (255-150)*(gdata.m_timeDelta * (1/dur)),
                                           lvlShot.getColor().b - (255-150)*(gdata.m_timeDelta * (1/dur)),
                                           lvlShot.getColor().a - (255-200)*(gdata.m_timeDelta * (1/dur))));

        //MOVE orx to rx
        if(rbLvlShot.getPosition().x > rx)
            rbLvlShot.setPosition(rbLvlShot.getPosition().x - (orx - rx) *(gdata.m_timeDelta * (1/dur)), cy);
        if(rbLvlShot.getScale().x < 0.2)
            rbLvlShot.setScale(rbLvlShot.getScale().x + ((0.2-0.1)*(gdata.m_timeDelta * (1/dur))),
                               rbLvlShot.getScale().y + ((0.2-0.1)*(gdata.m_timeDelta * (1/dur))));
        if(rbLvlShot.getColor().r < 150 )
            rbLvlShot.setColor(sf::Color(rbLvlShot.getColor().r + (150-100)*(gdata.m_timeDelta * (1/dur)),
                                           rbLvlShot.getColor().g + (150-100)*(gdata.m_timeDelta * (1/dur)),
                                           rbLvlShot.getColor().b + (150-100)*(gdata.m_timeDelta * (1/dur)),
                                           rbLvlShot.getColor().a + (200-100)*(gdata.m_timeDelta * (1/dur))));


        //MOVE lx to olx
        if(leftLvlShot.getPosition().x > olx)
            leftLvlShot.setPosition(leftLvlShot.getPosition().x - (lx + olx) *(gdata.m_timeDelta * (1/dur)), cy);
        if(leftLvlShot.getScale().x > 0.1)
            leftLvlShot.setScale(leftLvlShot.getScale().x - ((0.2-0.1)*(gdata.m_timeDelta * (1/dur))),
                                 leftLvlShot.getScale().y - ((0.2-0.1)*(gdata.m_timeDelta * (1/dur))));
        if(leftLvlShot.getColor().r > 100 )
            leftLvlShot.setColor(sf::Color(leftLvlShot.getColor().r - (150-100)*(gdata.m_timeDelta * (1/dur)),
                                           leftLvlShot.getColor().g - (150-100)*(gdata.m_timeDelta * (1/dur)),
                                           leftLvlShot.getColor().b - (150-100)*(gdata.m_timeDelta * (1/dur)),
                                           leftLvlShot.getColor().a - (200-100)*(gdata.m_timeDelta * (1/dur))));

        //MOVE rx to cx
        if(rightLvlShot.getPosition().x > cx)
            rightLvlShot.setPosition(rightLvlShot.getPosition().x - (rx - cx) *(gdata.m_timeDelta * (1/dur)),cy);
        if(rightLvlShot.getScale().x < 0.5)
            rightLvlShot.setScale(rightLvlShot.getScale().x + ((0.5-0.2)*(gdata.m_timeDelta * (1/dur))),
                                  rightLvlShot.getScale().y + ((0.5-0.2)*(gdata.m_timeDelta * (1/dur))));
        if(rightLvlShot.getColor().r < 255 )
            rightLvlShot.setColor(sf::Color(rightLvlShot.getColor().r + (255-150)*(gdata.m_timeDelta * (1/dur)),
                                                rightLvlShot.getColor().g + (255-150)*(gdata.m_timeDelta * (1/dur)),
                                                rightLvlShot.getColor().b + (255-150)*(gdata.m_timeDelta * (1/dur)),
                                                rightLvlShot.getColor().a + (255-200)*(gdata.m_timeDelta * (1/dur))));



        if(rightLvlShot.getPosition().x < cx)
        {
            slideLeft = false;

            leftLvlShot = lvlShot;
            lvlShot = rightLvlShot;
            rightLvlShot = rbLvlShot;
            rbLvlShot.setPosition(orx, cy);
            rbLvlShot.setScale(0.1,0.1);

            lvlShot.setPosition(cx,cy);
            rightLvlShot.setPosition(rx,cy);
            leftLvlShot.setPosition(lx,cy);
            rbLvlShot.setPosition(orx,cy);
            lbLvlShot.setPosition(olx,cy);

            lvlShot.setColor(sf::Color(255,255,255,255));
            leftLvlShot.setColor(sf::Color(150,150,150,200));
            rightLvlShot.setColor(sf::Color(150,150,150,200));
            lbLvlShot.setColor(sf::Color(100,100,100,100));
            rbLvlShot.setColor(sf::Color(100,100,100,100));

            selectedLevel += 1;
            if(selectedLevel > levelCount)
                selectedLevel = 1;

            leftLevel = selectedLevel - 1;
            if(leftLevel < 1)
                leftLevel = levelCount;

            rightLevel = selectedLevel + 1;
            if(rightLevel > levelCount)
                rightLevel = 1;

            lbLevel = leftLevel - 1;
            if(lbLevel < 1)
                lbLevel = levelCount;

            rbLevel = rightLevel + 1;
            if(rbLevel > levelCount)
                rbLevel = 1;

            lvlShot.setTexture(*gdata.assets->getTexture("Screencap_Level_"+gz::toString(selectedLevel)));
            leftLvlShot.setTexture(*gdata.assets->getTexture("Screencap_Level_"+gz::toString(leftLevel)));
            rightLvlShot.setTexture(*gdata.assets->getTexture("Screencap_Level_"+gz::toString(rightLevel)));
            lbLvlShot.setTexture(*gdata.assets->getTexture("Screencap_Level_"+gz::toString(lbLevel)));
            rbLvlShot.setTexture(*gdata.assets->getTexture("Screencap_Level_"+gz::toString(rbLevel)));
        }
    }

    if(slideRight)
    {
        //MOVE cx to rx
        if(lvlShot.getPosition().x < rx)
            lvlShot.setPosition(lvlShot.getPosition().x + (rx - cx) *(gdata.m_timeDelta * (1/dur)),cy);
        if(lvlShot.getScale().x > 0.2)
            lvlShot.setScale(lvlShot.getScale().x - ((0.5-0.2)*(gdata.m_timeDelta * (1/dur))),
                             lvlShot.getScale().y - ((0.5-0.2)*(gdata.m_timeDelta * (1/dur))));
        if(lvlShot.getColor().r > 150 )
            lvlShot.setColor(sf::Color(lvlShot.getColor().r - (255-150)*(gdata.m_timeDelta * (1/dur)),
                                           lvlShot.getColor().g - (255-150)*(gdata.m_timeDelta * (1/dur)),
                                           lvlShot.getColor().b - (255-150)*(gdata.m_timeDelta * (1/dur)),
                                           lvlShot.getColor().a - (255-200)*(gdata.m_timeDelta * (1/dur))));

        //MOVE olx to lx
        if(lbLvlShot.getPosition().x < lx)
            lbLvlShot.setPosition(lbLvlShot.getPosition().x + (lx + olx) *(gdata.m_timeDelta * (1/dur)), cy);
        if(lbLvlShot.getScale().x < 0.2)
            lbLvlShot.setScale(lbLvlShot.getScale().x + ((0.2-0.1)*(gdata.m_timeDelta * (1/dur))),
                               lbLvlShot.getScale().y + ((0.2-0.1)*(gdata.m_timeDelta * (1/dur))));
        if(lbLvlShot.getColor().r < 150 )
            lbLvlShot.setColor(sf::Color(lbLvlShot.getColor().r + (150-100)*(gdata.m_timeDelta * (1/dur)),
                                         lbLvlShot.getColor().g + (150-100)*(gdata.m_timeDelta * (1/dur)),
                                         lbLvlShot.getColor().b + (150-100)*(gdata.m_timeDelta * (1/dur)),
                                         lbLvlShot.getColor().a + (200-100)*(gdata.m_timeDelta * (1/dur))));


        //MOVE rx to orx
        if(rightLvlShot.getPosition().x < orx)
            rightLvlShot.setPosition(rightLvlShot.getPosition().x + (orx - rx) *(gdata.m_timeDelta * (1/dur)), cy);
        if(rightLvlShot.getScale().x > 0.1)
            rightLvlShot.setScale(rightLvlShot.getScale().x - ((0.2-0.1)*(gdata.m_timeDelta * (1/dur))),
                                  rightLvlShot.getScale().y - ((0.2-0.1)*(gdata.m_timeDelta * (1/dur))));
        if(rightLvlShot.getColor().r > 100 )
            rightLvlShot.setColor(sf::Color(rightLvlShot.getColor().r - (150-100)*(gdata.m_timeDelta * (1/dur)),
                                            rightLvlShot.getColor().g - (150-100)*(gdata.m_timeDelta * (1/dur)),
                                            rightLvlShot.getColor().b - (150-100)*(gdata.m_timeDelta * (1/dur)),
                                            rightLvlShot.getColor().a - (200-100)*(gdata.m_timeDelta * (1/dur))));

        //MOVE lx to cx
        if(leftLvlShot.getPosition().x < cx)
            leftLvlShot.setPosition(leftLvlShot.getPosition().x + (cx - lx) *(gdata.m_timeDelta * (1/dur)), cy);
        if(leftLvlShot.getScale().x < 0.5)
            leftLvlShot.setScale(leftLvlShot.getScale().x + ((0.5-0.2)*(gdata.m_timeDelta * (1/dur))),
                                 leftLvlShot.getScale().y + ((0.5-0.2)*(gdata.m_timeDelta * (1/dur))));
        if(leftLvlShot.getColor().r < 255 )
            leftLvlShot.setColor(sf::Color( leftLvlShot.getColor().r + (255-150)*(gdata.m_timeDelta * (1/dur)),
                                                leftLvlShot.getColor().g + (255-150)*(gdata.m_timeDelta * (1/dur)),
                                                leftLvlShot.getColor().b + (255-150)*(gdata.m_timeDelta * (1/dur)),
                                                leftLvlShot.getColor().a + (255-200)*(gdata.m_timeDelta * (1/dur))));


        if(leftLvlShot.getPosition().x > cx)
        {
            slideRight = false;

            rightLvlShot = lvlShot;
            lvlShot = leftLvlShot;
            leftLvlShot = lbLvlShot;
            lbLvlShot.setPosition(olx, cy);
            lbLvlShot.setScale(0.1,0.1);

            lvlShot.setPosition(cx,cy);
            rightLvlShot.setPosition(rx,cy);
            leftLvlShot.setPosition(lx,cy);
            rbLvlShot.setPosition(orx,cy);
            lbLvlShot.setPosition(olx,cy);

            lvlShot.setColor(sf::Color(255,255,255,255));
            leftLvlShot.setColor(sf::Color(150,150,150,200));
            rightLvlShot.setColor(sf::Color(150,150,150,200));
            lbLvlShot.setColor(sf::Color(100,100,100,100));
            rbLvlShot.setColor(sf::Color(100,100,100,100));

            selectedLevel -=1;
            if(selectedLevel < 1)
                selectedLevel = levelCount;

            leftLevel = selectedLevel - 1;
            if(leftLevel < 1)
                leftLevel = levelCount;

            rightLevel = selectedLevel + 1;
            if(rightLevel > levelCount)
                rightLevel = 1;

            lbLevel = leftLevel - 1;
            if(lbLevel < 1)
                lbLevel = levelCount;

            rbLevel = rightLevel + 1;
            if(rbLevel > levelCount)
                rbLevel = 1;

            lvlShot.setTexture(*gdata.assets->getTexture("Screencap_Level_"+gz::toString(selectedLevel)));
            leftLvlShot.setTexture(*gdata.assets->getTexture("Screencap_Level_"+gz::toString(leftLevel)));
            rightLvlShot.setTexture(*gdata.assets->getTexture("Screencap_Level_"+gz::toString(rightLevel)));
            lbLvlShot.setTexture(*gdata.assets->getTexture("Screencap_Level_"+gz::toString(lbLevel)));
            rbLvlShot.setTexture(*gdata.assets->getTexture("Screencap_Level_"+gz::toString(rbLevel)));
        }
    }
}

void StateMenu::draw()
{
    gdata.window->clear(sf::Color(255,255,255,255));
    bg.draw();

//    font.drawString(10, 10, gz::toString(gdata.mouse.x) + " " + gz::toString(gdata.mouse.y));
    gdata.window->draw(title);

    if(menuState == MENU_MAIN)
    {
        for(int i = 0; i < menuItems.size(); i++)
        {
            if(selected == i)
            {
                font.setColor(sf::Color::White);

                rec.setPosition(x, y + (78*i));
                rec.setSize(sf::Vector2f(500,70));
                rec.setFillColor(sf::Color::Red);
                gdata.window->draw(rec);

                font.drawString(x + 25, y + (78*i), menuItems[i]);

            }
            else
            {
                font.setColor(sf::Color::Black);
                font.drawString(x, y + (78*i), menuItems[i]);
            }
        }
    }

    else if(menuState == MENU_LEVELS)
    {
        y = gdata.settings->getScreenHeight() - 40 - (78 * 4);
        font.setColor(sf::Color::White);

        if(slideLeft)
            gdata.window->draw(rbLvlShot);
        if(slideRight)
            gdata.window->draw(lbLvlShot);
        gdata.window->draw(lvlShot);
        gdata.window->draw(leftLvlShot);
        gdata.window->draw(rightLvlShot);

        rec.setPosition(x, y);
        rec.setSize(sf::Vector2f(500,70));
        rec.setFillColor(sf::Color::Red);
        gdata.window->draw(rec);

        font.drawString(x + 25, y, "Level   " + gz::toString(selectedLevel));

        if(locked)
        {
            font.setColor(sf::Color::Black);
            font.drawString(cx, cy + (cy/2), "LEVEL LOCKED", sfLib::MIDDLE);
        }
    }

    else if(menuState == MENU_AWARDS)
    {

    }

    else if(menuState == MENU_OPTIONS)
    {
        for (int i = 0; i < optionsItems.size(); i++)
        {
            if(selectedOption == i)
            {
                rec.setPosition(x, y + (78*i));
                rec.setSize(sf::Vector2f(500,70));
                rec.setFillColor(sf::Color::Red);
                gdata.window->draw(rec);

                font.setColor(sf::Color::White);
                font.drawString(x + 25, y + (78*i), optionsItems[i]);
                if(!transitioning)
                {
                    font.setColor(sf::Color::Black);
                    font.drawString(x - 20, y + (78*i),optionsSettings[i][selectedOps[i]],sfLib::RIGHT);
                }
            }
            else
            {
                font.setColor(sf::Color::Black);
                font.drawString(x, y + (78*i), optionsItems[i]);
                if(!transitioning)
                {
                    font.setColor(sf::Color(210,210,210,255));
                    font.drawString(x - 20, y + (78*i),optionsSettings[i][selectedOps[i]],sfLib::RIGHT);
                }
            }
        }
    }

	gdata.window->display();
}

void StateMenu::freeResources()
{
    gdata.camera = nullptr;
    music.stop();
}

void StateMenu::start(){}
