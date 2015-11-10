#include "StateMenu.h"

StateMenu::StateMenu() : IState(STATE_MENU)
{
    //ctor
}

StateMenu::~StateMenu()
{
    //dtor
}

bool StateMenu::isTouching(Vector2 point, sf::RectangleShape box)
{
    if (point.x < box.getPosition().x) return false;
    if (point.y < box.getPosition().y) return false;

    if (point.x > box.getPosition().x + box.getSize().x - 1) return false;
    if (point.y > box.getPosition().y + box.getSize().y - 1) return false;

    return true;
}

bool StateMenu::isTouching(Vector2 point, sf::Sprite box)
{
    if (point.x < box.getPosition().x - ((box.getTexture()->getSize().x /2)* box.getScale().x)) return false;
    if (point.y < box.getPosition().y - ((box.getTexture()->getSize().y /2)* box.getScale().y)) return false;

    if (point.x > box.getPosition().x + ((box.getTexture()->getSize().x /2)* box.getScale().x) - 1) return false;
    if (point.y > box.getPosition().y + ((box.getTexture()->getSize().y /2)* box.getScale().y) - 1) return false;

    return true;
}

void StateMenu::load()
{
    gdata.camera = &c;
    //bg.bg_image.setTexture(*gdata.assets->getTexture("background"));
    bg.bubble_alpha_range.set(0,64);
    bg.rec.setFillColor(sf::Color(16,33,57));
    bg.bubble_color = sf::Color(0,0,0,255);
    bg.num_circles = 60;
    bg.init();

    //font = new sfFontRenderer(gdata.window);
    font.setWindow(gdata.window);
    font.setFont(gdata.assets->getFont("segoe-ui-light-48"));

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
    for (unsigned i = 0; i < modes.size(); i++)
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
            //levelCount += 3;
            break;
        }
    }

    cout << "Level count: " << levelCount << endl;

    //! CHANGE THIS WHEN MORE LEVELS ADDED !//
    for (int j = 0; j < 4 ; j++ )
    {
        // 9 levels per world
        int counter = 10;
        if(j == 3)
            counter = 9;

        for (int i = 1; i < counter ; i++ )
        {
            levelsInWorld.push_back(i + (j*9));
        }
        world.push_back(levelsInWorld);
        levelsInWorld.clear();
    }

    //hard coded because buggy
    levelCount = 35;

    leftLevel = 0;

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

    cout << gdata.settings->getVolume() << endl;
    gdata.audio->setVolumeMusic(gdata.settings->getVolume());
    gdata.audio->setVolumeSFX(gdata.settings->getSFX());

    title.setTexture(*gdata.assets->getTexture("title"));
    title.setOrigin(title.getTexture()->getSize().x/2,title.getTexture()->getSize().y/2);
    title.setPosition(gdata.settings->getScreenWidth()/2,150);

    // Make the music random
    srand(time(NULL));
    int randomMusic = rand() % 2 + 1;
    cout << "RandomMusic: " << randomMusic << endl;

    if (!gdata.bg_music)
    {
        if(randomMusic == 1)
            gdata.bg_music = gdata.audio->addMusic("music2");
        else
            gdata.bg_music = gdata.audio->addMusic("Divider");

        gdata.bg_music->loop(true);
    }

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
    if(gdata.keys[sf::Keyboard::Escape].isKeyPressed)
    {
        if(menuState == MENU_MAIN)
            gdata.running = false;
        else
        {
            transitioning = true;
            pushMenu = MENU_MAIN;
        }

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

            if(gdata.keys[KEY_MOUSE_LEFT].isKeyPressed)
            {
                if(isTouching(gdata.mouse_raw, startBox))
                {
                    gdata.audio->playSound("click");
                    transitioning = true;
                    pushMenu = MENU_LEVELS;
                }
                else if(isTouching(gdata.mouse_raw, achBox))
                {
                    gdata.audio->playSound("click");
                    transitioning = true;
                    pushMenu = MENU_AWARDS;
                }
                else if(isTouching(gdata.mouse_raw, optionsBox))
                {
                    gdata.audio->playSound("click");
                    transitioning = true;
                    pushMenu = MENU_OPTIONS;
                }

                else if(isTouching(gdata.mouse_raw, exitBox))
                {
                    gdata.audio->playSound("click");
                    gdata.running = false;
                }

            }

            if (gdata.keys[sf::Keyboard::Up].isKeyPressed)
            {
                selected -= 1;
                if(selected < 0)
                    selected = menuItems.size() -1;
            }

            else if (gdata.keys[sf::Keyboard::Down].isKeyPressed)
            {
                selected += 1;
                if(selected > static_cast<signed>(menuItems.size()) -1)
                    selected = 0;
            }


            else if(gdata.keys[sf::Keyboard::Return].isKeyPressed)
            {
                gdata.audio->playSound("click");
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

            else if(gdata.keys[KEY_MOUSE_RIGHT].isKeyPressed)
            {

                if(isTouching(gdata.mouse_raw, opsBox1))
                {
                    selectedOps[selectedOption] -= 1;
                    if(selectedOps[selectedOption] < 0 )
                        selectedOps[selectedOption] = optionsSettings[selectedOption].size()-1;
                    selectedVSync = selectedOps[selectedOption];
                }
                else if(isTouching(gdata.mouse_raw, opsBox2))
                {
                    selectedOps[selectedOption] -= 1;
                    if(selectedOps[selectedOption] < 0 )
                        selectedOps[selectedOption] = optionsSettings[selectedOption].size()-1;
                    selectedFs = selectedOps[selectedOption];
                }
                else if(isTouching(gdata.mouse_raw, opsBox3))
                {
                    selectedOps[selectedOption] -= 1;
                    if(selectedOps[selectedOption] < 0 )
                        selectedOps[selectedOption] = optionsSettings[selectedOption].size()-1;
                    selectedRes = selectedOps[selectedOption];
                }
                else if(isTouching(gdata.mouse_raw, opsBox4))
                {
                    selectedOps[selectedOption] -= 1;
                    if(selectedOps[selectedOption] < 0 )
                        selectedOps[selectedOption] = optionsSettings[selectedOption].size()-1;
                    selectedFPS = selectedOps[selectedOption];
                }
                else if(isTouching(gdata.mouse_raw, opsBox5))
                {
                    selectedOps[selectedOption] -= 1;
                    if(selectedOps[selectedOption] < 0 )
                        selectedOps[selectedOption] = optionsSettings[selectedOption].size()-1;
                    selectedMus = selectedOps[selectedOption];
                }
                else if(isTouching(gdata.mouse_raw, opsBox6))
                {
                    selectedOps[selectedOption] -= 1;
                    if(selectedOps[selectedOption] < 0 )
                        selectedOps[selectedOption] = optionsSettings[selectedOption].size()-1;
                    selectedSFX = selectedOps[selectedOption];
                }
                else if(isTouching(gdata.mouse_raw, opsBox7))
                {
                    selectedOps[selectedOption] += 1;
                    if(selectedOps[selectedOption] > static_cast<signed>(optionsSettings[selectedOption].size())-1)
                        selectedOps[selectedOption] = 0;
                    selectedSave = selectedOps[selectedOption];
                }
            }
            else if(gdata.keys[KEY_MOUSE_LEFT].isKeyPressed)
            {
                if(isTouching(gdata.mouse_raw, opsBox1))
                {
                    selectedOps[selectedOption] += 1;
                    if(selectedOps[selectedOption] > static_cast<signed>(optionsSettings[selectedOption].size())-1)
                        selectedOps[selectedOption] = 0;
                    selectedVSync = selectedOps[selectedOption];
                }
                else if(isTouching(gdata.mouse_raw, opsBox2))
                {
                    selectedOps[selectedOption] += 1;
                    if(selectedOps[selectedOption] > static_cast<signed>(optionsSettings[selectedOption].size())-1)
                        selectedOps[selectedOption] = 0;
                    selectedFs = selectedOps[selectedOption];
                }
                else if(isTouching(gdata.mouse_raw, opsBox3))
                {
                    selectedOps[selectedOption] += 1;
                    if(selectedOps[selectedOption] > static_cast<signed>(optionsSettings[selectedOption].size())-1)
                        selectedOps[selectedOption] = 0;
                    selectedRes = selectedOps[selectedOption];
                }
                else if(isTouching(gdata.mouse_raw, opsBox4))
                {
                    selectedOps[selectedOption] += 1;
                    if(selectedOps[selectedOption] > static_cast<signed>(optionsSettings[selectedOption].size())-1)
                        selectedOps[selectedOption] = 0;
                    selectedFPS = selectedOps[selectedOption];
                }
                else if(isTouching(gdata.mouse_raw, opsBox5))
                {
                    selectedOps[selectedOption] += 1;
                    if(selectedOps[selectedOption] > static_cast<signed>(optionsSettings[selectedOption].size())-1)
                        selectedOps[selectedOption] = 0;
                    selectedMus = selectedOps[selectedOption];
                }
                else if(isTouching(gdata.mouse_raw, opsBox6))
                {
                    selectedOps[selectedOption] += 1;
                    if(selectedOps[selectedOption] > static_cast<signed>(optionsSettings[selectedOption].size())-1)
                        selectedOps[selectedOption] = 0;
                    selectedSFX = selectedOps[selectedOption];
                }
                else if(isTouching(gdata.mouse_raw, opsBox7))
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

                        gdata.audio->setVolumeMusic(gdata.settings->getVolume());
                        gdata.audio->setVolumeSFX(gdata.settings->getSFX());

                        cout << "settings saved" << endl;

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

                    gdata.audio->setVolumeMusic(gdata.settings->getVolume());
                    gdata.audio->setVolumeSFX(gdata.settings->getSFX());

                    cout << "settings saved" << endl;

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
                if(selectedOption > static_cast<signed>(optionsItems.size()) -1)
                    selectedOption = 0;
            }

            else if (gdata.keys[sf::Keyboard::Right].isKeyPressed)
            {
                selectedOps[selectedOption] += 1;
                if(selectedOps[selectedOption] > static_cast<signed>(optionsSettings[selectedOption].size())-1)
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
            if(gdata.keys[sf::Keyboard::BackSpace].isKeyPressed || gdata.keys[KEY_MOUSE_RIGHT].isKeyPressed)
            {
//                menuState = MENU_MAIN;
                transitioning = true;
                pushMenu = MENU_MAIN;
            }
        }

        else if(menuState == MENU_LEVELS) //Handle events within the level select menu screen
        {
            if(gdata.keys[sf::Keyboard::BackSpace].isKeyPressed || gdata.keys[KEY_MOUSE_RIGHT].isKeyPressed)
            {
                transitioning = true;
                pushMenu = MENU_MAIN;
            }

            else if (gdata.keys[sf::Keyboard::Right].isKeyPressed)
            {
                if(!slideLeft && !slideRight && selectedLevel < levelCount)
                    slideLeft = true;
            }

            else if (gdata.keys[sf::Keyboard::Left].isKeyPressed)
            {
                if(!slideLeft && !slideRight && selectedLevel > 1) //world[selectedWorld][selectedLevel]
                    slideRight = true;
            }
//
//            else if (gdata.keys[sf::Keyboard::Down].isKeyPressed)
//            {
//                if(!slideLeft && !slideRight)
//                {
//                    if(selectedWorld < world.size()-1)
//                        selectedWorld += 1;
//                    else
//                        selectedWorld = 0;
//
//                    selectedLevel = 0;
//                }
//                refreshTextures();
//            }
//
//            else if (gdata.keys[sf::Keyboard::Up].isKeyPressed)
//            {
//                if(!slideLeft && !slideRight)
//                {
//                    if(selectedWorld > 0)
//                        selectedWorld -= 1;
//                    else
//                        selectedWorld = world.size() -1;
//
//                    selectedLevel = 0;
//                }
//                refreshTextures();
//            }

            else if (gdata.keys[sf::Keyboard::Return].isKeyPressed)
            {
                if(!locked)
                {
                    gdata.level = selectedLevel;
                    gdata.gamestate = STATE_GAME;
                }
            }
            else if(gdata.keys[KEY_MOUSE_LEFT].isKeyPressed)
            {
                if(selectedLevel < levelCount)
                {
                    if (isTouching(gdata.mouse_raw, rightLvlShot))
                    {
                        gdata.audio->playSound("click");
                        if(!slideLeft && !slideRight)
                            slideLeft = true;
                    }
                }
                if(selectedLevel > 1)
                {
                    if (isTouching(gdata.mouse_raw, leftLvlShot))
                    {
                        gdata.audio->playSound("click");
                        if(!slideLeft && !slideRight)
                            slideRight = true;
                    }
                }

                if (isTouching(gdata.mouse_raw, lvlShot))
                {
                    gdata.audio->playSound("click");
                    if(!slideLeft && !slideRight)
                        if(!locked)
                        {
                            gdata.level = selectedLevel;
                            gdata.gamestate = STATE_GAME;
                        }
                }
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
    for (unsigned i = 0; i < modes.size(); i++)
    {
        sf::VideoMode mode = modes[i];
        if(mode.width == gdata.settings->getScreenWidth() && mode.height == gdata.settings->getScreenHeight())
        {
            selectedRes = (modes.size() - 1) - i;
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
//    if(selectedLevel == levelCount - 1 || selectedLevel == levelCount - 2 || selectedLevel == levelCount)
//        locked = true;
//    else
    locked = false;

    //Correct position from the bottom of screen
    vector<string> vec;
    if (menuState == MENU_MAIN)
    {
        vec = menuItems;
        if(isTouching(gdata.mouse_raw, startBox))
        {
            selected = 0;
            gdata.audio->playSound("menu_click");
        }
        else if(isTouching(gdata.mouse_raw, achBox))
        {
            selected = 1;
            gdata.audio->playSound("menu_click");
        }
        else if(isTouching(gdata.mouse_raw, optionsBox))
        {
            selected = 2;
            gdata.audio->playSound("menu_click");
        }
        else if(isTouching(gdata.mouse_raw, exitBox))
        {
            selected = 3;
            gdata.audio->playSound("menu_click");
        }
    }
    else if (menuState == MENU_OPTIONS)
    {
        vec = optionsItems;
        if(isTouching(gdata.mouse_raw, opsBox1))
        {
            selectedOption = 0;
        }
        else if(isTouching(gdata.mouse_raw, opsBox2))
        {
            selectedOption = 1;
        }
        else if(isTouching(gdata.mouse_raw, opsBox3))
        {
            selectedOption = 2;
        }
        else if(isTouching(gdata.mouse_raw, opsBox4))
        {
            selectedOption = 3;
        }
        else if(isTouching(gdata.mouse_raw, opsBox5))
        {
            selectedOption = 4;
        }
        else if(isTouching(gdata.mouse_raw, opsBox6))
        {
            selectedOption = 5;
        }
        else if(isTouching(gdata.mouse_raw, opsBox7))
        {
            selectedOption = 6;
        }
    }
    else if(menuState == MENU_LEVELS)
    {
        if(selectedLevel < 10)
            selectedWorld = 1;
        if(selectedLevel >= 10 && selectedLevel < 19)
            selectedWorld = 2;
        if(selectedLevel >= 19 && selectedLevel < 28)
            selectedWorld = 3;
        if(selectedLevel >= 28)
            selectedWorld = 4;
    }

    mx = gdata.settings->getScreenWidth() - 400;
    tx = gdata.settings->getScreenWidth() + 10;
    y = gdata.settings->getScreenHeight() - 100 - (78 * vec.size());


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
        }
    }

    //RIGHT KEY PRESSED
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
//            if(selectedLevel > world[selectedWorld].size()-1)
//                selectedLevel = 0;

            leftLevel = selectedLevel - 1;
//            if(leftLevel < 0)
//                leftLevel = world[selectedWorld].size()-1;

            rightLevel = selectedLevel + 1;
//            if(rightLevel > world[selectedWorld].size()-1)
//                rightLevel = 0;

            lbLevel = leftLevel - 1;
//            if(lbLevel < 0)
//                lbLevel = world[selectedWorld].size()-1;

            rbLevel = rightLevel + 1;
//            if(rbLevel > world[selectedWorld].size()-1)
//                rbLevel = 0;

            refreshTextures();
        }
    }

    //LEFT KEY PRESSED
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
//            if(selectedLevel < 0)
//                selectedLevel = world[selectedWorld].size()-1;

            leftLevel = selectedLevel - 1;
//            if(leftLevel < 0)
//                leftLevel = world[selectedWorld].size()-1;

            rightLevel = selectedLevel + 1;
//            if(rightLevel > world[selectedWorld].size()-1)
//                rightLevel = 0;

            lbLevel = leftLevel - 1;
//            if(lbLevel < 0)
//                lbLevel = world[selectedWorld].size()-1;

            rbLevel = rightLevel + 1;
//            if(rbLevel > world[selectedWorld].size()-1)
//                rbLevel = 0;

            refreshTextures();
        }
    }
}

void StateMenu::refreshTextures()
{
//    lvlShot.setTexture(*gdata.assets->getTexture("Screencap_Level_"+gz::toString(world[selectedWorld][selectedLevel])));
//    leftLvlShot.setTexture(*gdata.assets->getTexture("Screencap_Level_"+gz::toString(world[selectedWorld][leftLevel])));
//    rightLvlShot.setTexture(*gdata.assets->getTexture("Screencap_Level_"+gz::toString(world[selectedWorld][rightLevel])));
//    lbLvlShot.setTexture(*gdata.assets->getTexture("Screencap_Level_"+gz::toString(world[selectedWorld][lbLevel])));
//    rbLvlShot.setTexture(*gdata.assets->getTexture("Screencap_Level_"+gz::toString(world[selectedWorld][rbLevel])));

    if(leftLevel < 0)
        leftLevel = 0;
    if(rightLevel > levelCount+1)
        rightLevel = 0;
    if(lbLevel < 0)
        leftLevel = 0;
    if(rbLevel > levelCount+1)
        rightLevel = 0;

    lvlShot.setTexture(*gdata.assets->getTexture("Screencap_Level_"+gz::toString(selectedLevel)));
    leftLvlShot.setTexture(*gdata.assets->getTexture("Screencap_Level_"+gz::toString(leftLevel)));
    rightLvlShot.setTexture(*gdata.assets->getTexture("Screencap_Level_"+gz::toString(rightLevel)));
    lbLvlShot.setTexture(*gdata.assets->getTexture("Screencap_Level_"+gz::toString(lbLevel)));
    rbLvlShot.setTexture(*gdata.assets->getTexture("Screencap_Level_"+gz::toString(rbLevel)));

    if(leftLevel < 0)
        leftLvlShot.setColor(sf::Color::Transparent);
    else
        leftLvlShot.setColor(sf::Color::White);
    if(rightLevel > levelCount)
        rightLvlShot.setColor(sf::Color::Transparent);
    else
        rightLvlShot.setColor(sf::Color::White);

    if(lbLevel < 1)
        lbLvlShot.setColor(sf::Color::Transparent);
    else
        lbLvlShot.setColor(sf::Color::White);

    if(rbLevel > levelCount)
        rbLvlShot.setColor(sf::Color::Transparent);
    else
        rbLvlShot.setColor(sf::Color::White);
    lvlShot.setColor(sf::Color::White);
}

void StateMenu::updateMenuBox()
{
    startBox.setSize(sf::Vector2f(500, 70));
    startBox.setPosition(x, y + (78*0));
    startBox.setFillColor(sf::Color::Transparent);

    achBox.setSize(sf::Vector2f(500, 70));
    achBox.setPosition(x, y + (78*1));
    achBox.setFillColor(sf::Color::Transparent);

    optionsBox.setSize(sf::Vector2f(500, 70));
    optionsBox.setPosition(x, y + (78*2));
    optionsBox.setFillColor(sf::Color::Transparent);

    exitBox.setSize(sf::Vector2f(500, 70));
    exitBox.setPosition(x, y + (78*3));
    exitBox.setFillColor(sf::Color::Transparent);
}

void StateMenu::updateOpsBox()
{
    opsBox1.setSize(sf::Vector2f(500, 70));
    opsBox1.setPosition(x, y + (78*0));
    opsBox1.setFillColor(sf::Color::Transparent);

    opsBox2.setSize(sf::Vector2f(500, 70));
    opsBox2.setPosition(x, y + (78*1));
    opsBox2.setFillColor(sf::Color::Transparent);

    opsBox3.setSize(sf::Vector2f(500, 70));
    opsBox3.setPosition(x, y + (78*2));
    opsBox3.setFillColor(sf::Color::Transparent);

    opsBox4.setSize(sf::Vector2f(500, 70));
    opsBox4.setPosition(x, y + (78*3));
    opsBox4.setFillColor(sf::Color::Transparent);

    opsBox5.setSize(sf::Vector2f(500, 70));
    opsBox5.setPosition(x, y + (78*4));
    opsBox5.setFillColor(sf::Color::Transparent);

    opsBox6.setSize(sf::Vector2f(500, 70));
    opsBox6.setPosition(x, y + (78*5));
    opsBox6.setFillColor(sf::Color::Transparent);

    opsBox7.setSize(sf::Vector2f(500, 70));
    opsBox7.setPosition(x, y + (78*6));
    opsBox7.setFillColor(sf::Color::Transparent);

}

void StateMenu::draw()
{
    bg.draw();

//    font.drawString(10, 10, gz::toString(gdata.mouse.x) + " " + gz::toString(gdata.mouse.y));
    gdata.window->draw(title);

    if(menuState == MENU_MAIN)
    {
        updateMenuBox();
        gdata.window->draw(exitBox);
        gdata.window->draw(achBox);
        gdata.window->draw(optionsBox);
        gdata.window->draw(startBox);

        for(unsigned i = 0; i < menuItems.size(); i++)
        {
            if(selected == static_cast<signed>(i))
            {
                font.setColor(sf::Color::Black);

                rec.setPosition(x, y + (78*i));
                rec.setSize(sf::Vector2f(500,70));
                rec.setFillColor(sf::Color::White);
                gdata.window->draw(rec);

                font.drawString(x + 25, y + (78*i), menuItems[i]);

            }
            else
            {
                font.setColor(sf::Color::White);
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

//        rec.setPosition(x, y);
//        rec.setSize(sf::Vector2f(500,70));
//        rec.setFillColor(sf::Color::Red);
//        gdata.window->draw(rec);
//
//        font.drawString(x + 25, y, "Level   " + gz::toString(selectedLevel));

        if(locked)
        {
            font.setColor(sf::Color::White);
            font.drawString(cx, cy + (cy/2), "LEVEL LOCKED", Align::MIDDLE);
        }
        else
        {
            font.setColor(sf::Color::White);
            font.drawString(cx, cy + (cy/2), "WORLD " + gz::toString(selectedWorld), Align::MIDDLE);
            font.drawString(cx, cy + (cy/1.5), "LEVEL " + gz::toString(selectedLevel), Align::MIDDLE);
        }
    }

    else if(menuState == MENU_AWARDS)
    {

    }

    else if(menuState == MENU_OPTIONS)
    {
        updateOpsBox();
        gdata.window->draw(opsBox1);
        gdata.window->draw(opsBox2);
        gdata.window->draw(opsBox3);
        gdata.window->draw(opsBox4);
        gdata.window->draw(opsBox5);
        gdata.window->draw(opsBox6);
        gdata.window->draw(opsBox7);

        for (unsigned i = 0; i < optionsItems.size(); i++)
        {
            if(selectedOption == static_cast<signed>(i))
            {
                rec.setPosition(x, y + (78*i));
                rec.setSize(sf::Vector2f(500,70));
                rec.setFillColor(sf::Color::White);
                gdata.window->draw(rec);

                font.setColor(sf::Color::Black);
                font.drawString(x + 25, y + (78*i), optionsItems[i]);
                if(!transitioning)
                {
                    font.setColor(sf::Color::White);
                    font.drawString(x - 20, y + (78*i),optionsSettings[i][selectedOps[i]],Align::RIGHT);
                }
            }
            else
            {
                font.setColor(sf::Color::White);
                font.drawString(x, y + (78*i), optionsItems[i]);
                if(!transitioning)
                {
                    font.setColor(sf::Color(210,210,210,255));
                    font.drawString(x - 20, y + (78*i),optionsSettings[i][selectedOps[i]],Align::RIGHT);
                }
            }
        }
    }
}

void StateMenu::freeResources()
{
    gdata.camera = nullptr;
}

void StateMenu::start() {}
