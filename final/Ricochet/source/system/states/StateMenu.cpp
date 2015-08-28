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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
        {
            if(selected == 0) //Start
            {
                //
            }
            if(selected == 1) //Achievements
            {
                //
            }
            if(selected == 2) //Options
            {
                //
            }
            if(selected == 3) //Exit
            {
                gdata.running = false;
            }

        }
    }
}

void StateMenu::update(){}

void StateMenu::draw()
{
    gdata.window->clear(sf::Color(64,64,64,255));


    font->drawString(0,0,"hello this is a test");

    float x = gdata.settings->getScreenWidth() - 200;
    float y = 100;

    for(int i = 0; i < menuItems.size(); i++)
    {
        if(selected == i)
        {
            font->setColor(sf::Color::Cyan);
            font->drawString(x - 50,y, menuItems[i]);
        }
        else
        {
            font->setColor(sf::Color::White);
            font->drawString(x, y, menuItems[i]);
        }
        y += 100;
    }



	gdata.window->display();
}

void StateMenu::freeResources(){}
void StateMenu::start(){}
