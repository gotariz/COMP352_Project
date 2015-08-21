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

    font = new sfFontRenderer(gdata.window);
    font->setFont(assets.getFont("purista-medium-14-white"));


	gdata.zoom = (gdata.settings->getScreenWidth() / 1920.f);

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
}

void StateMenu::update(){}

void StateMenu::draw()
{
    gdata.window->clear(sf::Color(64,64,64,255));


    font->drawString(0,0,"hello this is a test");
	gdata.window->display();
}

void StateMenu::freeResources(){}
void StateMenu::start(){}
