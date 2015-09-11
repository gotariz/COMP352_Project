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

    Camera c(0,0,0,0);
    gdata.camera = &c;
    //bg.bg_image.setTexture(*gdata.assets->getTexture("background"));
    bg.num_circles = 60;
    bg.bubble_alpha_range.set(0,128);
    bg.bubble_color = sf::Color(0,0,0,0);
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

    selectedOps.push_back(selectedVSync);
    selectedOps.push_back(selectedFs);
    selectedOps.push_back(selectedRes);
    selectedOps.push_back(selectedFPS);

	optionsItems.push_back("Vsync");
	optionsItems.push_back("Fullscreen");
	optionsItems.push_back("Resolution");
	optionsItems.push_back("FPS Limit");

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
            break;
        }
    }

	cout << "Level count: " << levelCount << endl;

	leftLevel = levelCount;

    mx = gdata.settings->getScreenWidth() - 400;
    tx = gdata.settings->getScreenWidth() + 10;
    y = gdata.settings->getScreenHeight() - 40 - (78 * 4);

    cx = gdata.settings->getScreenWidth()/2;
    rx = gdata.settings->getScreenWidth() - 20;
    lx = 20;

    oy = gdata.settings->getScreenHeight()/3;
    cy = gdata.settings->getScreenHeight()/4;

    x = mx;

    lvlShot.setPosition(cx - (gdata.settings->getScreenWidth() /2 * 0.5 ), cy);
    lvlShot.setScale(0.5,0.5);
    lvlShot.setSize(sf::Vector2f(gdata.settings->getScreenWidth(), gdata.settings->getScreenHeight()));

    leftLvlShot.setScale(0.2,0.2);
    leftLvlShot.setPosition(lx, oy);
    leftLvlShot.setFillColor(sf::Color(150,150,150,200));
    leftLvlShot.setSize(sf::Vector2f(gdata.settings->getScreenWidth(), gdata.settings->getScreenHeight()));

    rightLvlShot.setPosition(rx - (gdata.settings->getScreenWidth() * 0.2), oy);
    rightLvlShot.setScale(0.2,0.2);
    rightLvlShot.setFillColor(sf::Color(150,150,150,200));
    rightLvlShot.setSize(sf::Vector2f(gdata.settings->getScreenWidth(), gdata.settings->getScreenHeight()));

    rbLvlShot.setPosition(gdata.settings->getScreenWidth() + 20, oy);
    rbLvlShot.setScale(0.1,0.1);
    rbLvlShot.setFillColor(sf::Color(150,150,150,100));
    rbLvlShot.setSize(sf::Vector2f(gdata.settings->getScreenWidth(), gdata.settings->getScreenHeight()));

    lbLvlShot.setPosition(0 - (gdata.settings->getScreenWidth() * 0.2) - 20, oy);
    lbLvlShot.setScale(0.1,0.1);
    lbLvlShot.setFillColor(sf::Color(150,150,150,100));
    lbLvlShot.setSize(sf::Vector2f(gdata.settings->getScreenWidth(), gdata.settings->getScreenHeight()));

    music.stop();
    music.setLoop(true);
    music.openFromFile(gdata.assets->getMusic("music2"));
    music.setVolume(50);
    music.play();

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

                gdata.settings->saveSettings();

                gdata.window->setSize(sf::Vector2u(gdata.settings->getScreenWidth(),gdata.settings->getScreenHeight()));
                gdata.view = new sf::View(sf::FloatRect(0,0,gdata.settings->getScreenWidth(),gdata.settings->getScreenHeight()));
                gdata.window->setView(*gdata.view);
                gdata.window->setFramerateLimit(gdata.settings->getFpsLimit());
                gdata.window->setVerticalSyncEnabled(vSyncMode);

                cout << "\n<----------------------SETTINGS SAVED-------------------------->\n"
                     << "\tvSync:\t\t\t\t" << vSyncMode << "\n"
                     << "\tFullscreen:\t\t\t" << selectedFs << "\n"
                     << "\tResolution:\t\t\t" << gz::splitString(optionsSettings[2][selectedRes], 'x')[0] << "x"
                     << gz::splitString(optionsSettings[2][selectedRes], 'x')[1] << "\n"
                     << "\tFPS Limit:\t\t\t" << gz::stringToUnsigned(optionsSettings[3][selectedFPS]) << endl;

                mx = gdata.settings->getScreenWidth() - 400;
                tx = gdata.settings->getScreenWidth() + 10;
                y = gdata.settings->getScreenHeight() - 40 - (78 * 4);
                x = mx;

                cx = gdata.settings->getScreenWidth()/2;
                rx = gdata.settings->getScreenWidth() - 20;
                lx = 20;

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
                slideLeft = true;
            }

            else if (gdata.keys[sf::Keyboard::Left].isKeyPressed)
            {
                slideRight = true;
            }

            else if (gdata.keys[sf::Keyboard::Return].isKeyPressed)
            {
                gdata.level = selectedLevel;
                gdata.gamestate = STATE_GAME;
                music.stop();
            }
        }
    }
}

void StateMenu::reset()
{
    gdata.settings->setScreenWidth(600);
    gdata.settings->setScreenHeight(400);

    gdata.settings->saveSettings();

    gdata.window->setSize(sf::Vector2u(gdata.settings->getScreenWidth(),gdata.settings->getScreenHeight()));
    gdata.view = new sf::View(sf::FloatRect(0,0,gdata.settings->getScreenWidth(),gdata.settings->getScreenHeight()));
    gdata.window->setView(*gdata.view);
    gdata.window->setFramerateLimit(gdata.settings->getFpsLimit());
}

void StateMenu::update()
{
    bg.update();

    //Correct position from the bottom of screen
    vector<string> vec;
    if (menuState == MENU_MAIN)
        vec = menuItems;
    else if (menuState == MENU_OPTIONS)
        vec = optionsItems;

    mx = gdata.settings->getScreenWidth() - 400;
    tx = gdata.settings->getScreenWidth() + 10;
    y = gdata.settings->getScreenHeight() - 40 - (78 * vec.size());

    cx = gdata.settings->getScreenWidth()/2;
    rx = gdata.settings->getScreenWidth() - 20;
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

    if(slideLeft)
    {
        lvlShot.setPosition(lvlShot.getPosition().x - (cx - lx) *(gdata.m_timeDelta * (1/dur)),
                            lvlShot.getPosition().y - (cy - oy) *(gdata.m_timeDelta * (1/dur)));

        if(lvlShot.getScale().x > 0.2)
        {
            lvlShot.setScale(lvlShot.getScale().x - 0.02, lvlShot.getScale().y - 0.02);
        }

        if(lvlShot.getPosition().x <= lx )
        {
            lvlShot.setPosition(lx, oy);
        }



        rbLvlShot.setPosition(rbLvlShot.getPosition().x - (gdata.settings->getScreenWidth() +20 - (rx - (gdata.settings->getScreenWidth() * 0.2))) *(gdata.m_timeDelta * (1/dur)), oy);
        if(rbLvlShot.getScale().x < 0.2)
        {
            rbLvlShot.setScale(rbLvlShot.getScale().x + 0.01, rbLvlShot.getScale().y + 0.01);
        }

        if(rbLvlShot.getPosition().x <= (rx - (gdata.settings->getScreenWidth() * 0.2)))
        {
            rbLvlShot.setPosition((rx - (gdata.settings->getScreenWidth() * 0.2)), oy);
        }



        leftLvlShot.setPosition(leftLvlShot.getPosition().x - (gdata.settings->getScreenWidth() * 0.2) *(gdata.m_timeDelta * (1/dur)), oy);

        if(leftLvlShot.getScale().x > 0.1)
        {
            leftLvlShot.setScale(leftLvlShot.getScale().x - 0.02, leftLvlShot.getScale().y - 0.02);
        }

        if(leftLvlShot.getPosition().x <= 0 - (gdata.settings->getScreenWidth() * 0.2) )
        {
            leftLvlShot.setPosition(0 - (gdata.settings->getScreenWidth() * 0.2), oy);
        }


        rightLvlShot.setPosition(rightLvlShot.getPosition().x - (rx - cx) *(gdata.m_timeDelta * (1/dur)),
                                 rightLvlShot.getPosition().y + (cy - oy) *(gdata.m_timeDelta * (1/dur)));

        if(rightLvlShot.getScale().x < 0.5)
        {
            rightLvlShot.setScale(rightLvlShot.getScale().x + 0.02, rightLvlShot.getScale().y + 0.02);
        }

        if(rightLvlShot.getPosition().x <= cx - (gdata.settings->getScreenWidth() /2 * 0.5 ))
        {
            rightLvlShot.setPosition(cx - (gdata.settings->getScreenWidth() /2 * 0.5 ), cy);
        }

        if(rightLvlShot.getPosition() == sf::Vector2f(cx - (gdata.settings->getScreenWidth() /2 * 0.5 ), cy))
        {
            slideLeft = false;

            leftLvlShot = lvlShot;
            lvlShot = rightLvlShot;
            rightLvlShot = rbLvlShot;
            rbLvlShot.setPosition(gdata.settings->getScreenWidth() + 20, oy);
            rbLvlShot.setScale(0.1,0.1);

            lvlShot.setFillColor(sf::Color(255,255,255,255));
            leftLvlShot.setFillColor(sf::Color(150,150,150,200));
            rightLvlShot.setFillColor(sf::Color(150,150,150,200));


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
        }
    }

    if(slideRight)
    {
        lvlShot.setPosition(lvlShot.getPosition().x + (rx - (cx - (gdata.settings->getScreenWidth() /2 * 0.5 ))) *(gdata.m_timeDelta * (1/dur)),
                            lvlShot.getPosition().y - (cy - oy) *(gdata.m_timeDelta * (1/dur)));

        if(lvlShot.getScale().x > 0.2)
        {
            lvlShot.setScale(lvlShot.getScale().x - 0.02, lvlShot.getScale().y - 0.02);
        }

        if(lvlShot.getPosition().x >= (rx - (gdata.settings->getScreenWidth() * 0.2)))
        {
            lvlShot.setPosition((rx - (gdata.settings->getScreenWidth() * 0.2)), oy);
        }



        lbLvlShot.setPosition(lbLvlShot.getPosition().x + (gdata.settings->getScreenWidth() +20 - (rx - (gdata.settings->getScreenWidth() * 0.2))) *(gdata.m_timeDelta * (1/dur)), oy);
        if(lbLvlShot.getScale().x < 0.2)
        {
            lbLvlShot.setScale(lbLvlShot.getScale().x + 0.01, lbLvlShot.getScale().y + 0.01);
        }

        if(lbLvlShot.getPosition().x >= lx)
        {
            lbLvlShot.setPosition(lx, oy);
        }



        rightLvlShot.setPosition(rightLvlShot.getPosition().x + gdata.settings->getScreenWidth() *(gdata.m_timeDelta * (1/dur)), oy);

        if(rightLvlShot.getScale().x > 0.1)
        {
            rightLvlShot.setScale(rightLvlShot.getScale().x - 0.02, rightLvlShot.getScale().y - 0.02);
        }

        if(rightLvlShot.getPosition().x >= gdata.settings->getScreenWidth())
        {
            rightLvlShot.setPosition(gdata.settings->getScreenWidth(), oy);
        }


        leftLvlShot.setPosition(leftLvlShot.getPosition().x + (cx - (gdata.settings->getScreenWidth() /2 * 0.5 ) - lx) *(gdata.m_timeDelta * (1/dur)),
                                leftLvlShot.getPosition().y + (cy - oy) *(gdata.m_timeDelta * (1/dur)));

        if(leftLvlShot.getScale().x < 0.5)
        {
            leftLvlShot.setScale(leftLvlShot.getScale().x + 0.02, leftLvlShot.getScale().y + 0.02);
        }

        if(leftLvlShot.getPosition().x >= cx - (gdata.settings->getScreenWidth() /2 * 0.5 ))
        {
            leftLvlShot.setPosition(cx - (gdata.settings->getScreenWidth() /2 * 0.5 ), cy);
        }

        if(leftLvlShot.getPosition() == sf::Vector2f(cx - (gdata.settings->getScreenWidth() /2 * 0.5 ), cy))
        {
            slideRight = false;

            rightLvlShot = lvlShot;
            lvlShot = leftLvlShot;
            leftLvlShot = lbLvlShot;
            lbLvlShot.setPosition(0 - (gdata.settings->getScreenWidth() /2 * 0.2 ), oy);
            lbLvlShot.setScale(0.1,0.1);

            lvlShot.setFillColor(sf::Color(255,255,255,255));
            leftLvlShot.setFillColor(sf::Color(150,150,150,200));
            rightLvlShot.setFillColor(sf::Color(150,150,150,200));

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
        }
    }
}

void StateMenu::draw()
{
    gdata.window->clear(sf::Color(255,255,255,255));
    bg.draw();

//    font.drawString(10, 10, gz::toString(gdata.mouse.x) + " " + gz::toString(gdata.mouse.y));

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

//        rbLvlShot.setFillColor(sf::Color(0,0,255,100));     // BLUE
//        lbLvlShot.setFillColor(sf::Color(255,255,0,100));   // YELLOW
//        lvlShot.setFillColor(sf::Color(0,0,0,100));         // BLACK
//        rightLvlShot.setFillColor(sf::Color(0,255,0,100));  // GREEN
//        leftLvlShot.setFillColor(sf::Color(255,0,0,100));   // RED

        lvlShot.setTexture(gdata.assets->getTexture("Screencap_Level_"+gz::toString(selectedLevel)), true);
        leftLvlShot.setTexture(gdata.assets->getTexture("Screencap_Level_"+gz::toString(leftLevel)), true);
        rightLvlShot.setTexture(gdata.assets->getTexture("Screencap_Level_"+gz::toString(rightLevel)), true);
        lbLvlShot.setTexture(gdata.assets->getTexture("Screencap_Level_"+gz::toString(lbLevel)), true);
        rbLvlShot.setTexture(gdata.assets->getTexture("Screencap_Level_"+gz::toString(rbLevel)), true);

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

        font.drawString(x + 25, y, "Level");

        if(!transitioning)
        {
            font.setColor(sf::Color::Black);
            font.drawString(x - 20, y, gz::toString(selectedLevel),sfLib::RIGHT);
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
