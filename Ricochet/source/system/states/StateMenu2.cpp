#include "StateMenu2.h"

StateMenu2::StateMenu2() : IState(STATE_MENU)
{
    //ctor
}

StateMenu2::~StateMenu2()
{
    //dtor
}

void StateMenu2::load()
{
    int cx = gdata.settings->getScreenWidth() / 2;
    int cy = gdata.settings->getScreenHeight() / 2;
    gdata.camera = &c;

    // set background data
    background.bubble_alpha_range.set(0,64);
    background.rec.setFillColor(sf::Color(16,33,57));
    background.bubble_color = sf::Color(0,0,0);
    background.num_circles = 60;
    background.init();

    font.setWindow(gdata.window);
    font.setFont(gdata.assets->getFont("segoe-ui-light-48"));

    title.setTexture(*gdata.assets->getTexture("title"));
    title.setOrigin( title.getTexture()->getSize().x / 2, 0 );
    title.setPosition(cx,20);

    mm_init();
    om_init();
    ls_init();
}

void StateMenu2::mm_init()
{
    mm_items.push_back("Start");
    mm_items.push_back("Achievements");
    mm_items.push_back("Settings");
    mm_items.push_back("Exit");
}

void StateMenu2::om_init()
{
    om_items.push_back("Resolution");
    om_items.push_back("Screen Mode");
    om_items.push_back("V-Sync");
    om_items.push_back("FPS Limit");
    om_items.push_back("SFX Volume");
    om_items.push_back("Music Volume");
}

void StateMenu2::ls_init()
{

    int w = gdata.settings->getScreenWidth();
    int h = gdata.settings->getScreenHeight();
    int sx = (152 * 9) + (25 * 8);
    int sy = 500;

    int r = 0;
    int c = 0;

    for (int i = 0; i < 35; ++i)
    {
        LevelIcon li;
        li.init();
        li.rec.setSize(sf::Vector2f(152,84));
        li.rec.setTexture(gdata.assets->getTexture("SSL" + gz::toString(i + 1)));

        int x = (w/2) - (sx/2) + (c * (152 + 25));
        int y = 500 + r * 110;
        li.rec.setPosition(x,y);

        icons.push_back(li);

        ++c;
        if (c == 9)
        {
            c = 0;
            ++r;
        }

    }
}

bool StateMenu2::initialise()
{
    load();
}

void StateMenu2::handleEvents()
{
    sf::Event event;
    while (gdata.window->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            gdata.running = false;
        }
    }

    if (screen == 0)        mm_handleEvents();
    else if (screen == 1)   om_handleEvents();
    else if (screen == 2)   ls_handleEvents();
}

void StateMenu2::mm_handleEvents()
{
    if (gdata.keys[sf::Keyboard::Up].isKeyPressed)
    {
        if (mm_selected > 0)
            --mm_selected;
    }
    if (gdata.keys[sf::Keyboard::Down].isKeyPressed)
    {
        if (mm_selected < mm_items.size()-1)
            ++mm_selected;
    }

    // handle mouse events (mouse over menu items)
    int h = gdata.settings->getScreenHeight();
    int w = gdata.settings->getScreenWidth();

    bool onItem = false;
    for (int i = 0; i < mm_items.size(); ++i)
    {
        int x = w-ITEM_WIDTH;
        int y = h-BOTTOM_BUFFER-(mm_items.size()-i)*ITEM_SPACING;

        if (utils::isTouching(gdata.mouse_raw,x-10,y+5,BOX_WIDTH,ITEM_SPACING))
        {
            mm_selected = i;
            onItem = true;
        }
    }

    //clicking menu items
    if ( gdata.keys[sf::Keyboard::Return].isKeyPressed || (gdata.keys[KEY_MOUSE_LEFT].isKeyPressed && onItem) )
    {
        if (mm_selected == 0)       screen = 2;// go to level select
        else if (mm_selected == 1)  ;// go to achievements
        else if (mm_selected == 2)  screen = 1;// go to settings
        else if (mm_selected == 3)  gdata.running = false;// exit
    }

    if (gdata.keys[sf::Keyboard::Escape].isKeyPressed)
        gdata.running = false;
}

void StateMenu2::om_handleEvents()
{
        if (gdata.keys[sf::Keyboard::Up].isKeyPressed)
    {
        if (om_selected > 0)
            --om_selected;
    }
    if (gdata.keys[sf::Keyboard::Down].isKeyPressed)
    {
        if (om_selected < mm_items.size()-1)
            ++om_selected;
    }

    // handle mouse events (mouse over menu items)
    int h = gdata.settings->getScreenHeight();
    int w = gdata.settings->getScreenWidth();

    bool onItem = false;
    for (int i = 0; i < om_items.size(); ++i)
    {
        int x = w-ITEM_WIDTH;
        int y = h-BOTTOM_BUFFER-(om_items.size()-i)*ITEM_SPACING;

        if (utils::isTouching(gdata.mouse_raw,x-10,y+5,BOX_WIDTH,ITEM_SPACING))
        {
            om_selected = i;
            onItem = true;
        }
    }

    //clicking menu items
    if ( gdata.keys[sf::Keyboard::Return].isKeyPressed || (gdata.keys[KEY_MOUSE_LEFT].isKeyPressed && onItem) )
    {
    }

    if (gdata.keys[sf::Keyboard::Escape].isKeyPressed)
        screen = 0;
}

void StateMenu2::ls_handleEvents()
{
    for (int i = 0; i < icons.size(); ++i)
    {
        icons.at(i).hover = utils::isTouching(gdata.mouse_raw,icons.at(i).rec);
        if (icons.at(i).hover && gdata.keys[KEY_MOUSE_LEFT].isKeyPressed)
        {
            gdata.level = i + 1;
            gdata.gamestate = STATE_GAME;
        }

    }

    if (gdata.keys[sf::Keyboard::Escape].isKeyPressed)
        screen = 0;
}


void StateMenu2::update()
{
    background.update();

    if (screen == 0)        mm_update();
    else if (screen == 1)   om_update();
    else if (screen == 2)   ls_update();
}

void StateMenu2::mm_update()
{

}

void StateMenu2::om_update()
{

}

void StateMenu2::ls_update()
{
    for (int i = 0; i < icons.size(); ++i)
    {
        icons.at(i).update();
    }
}

void StateMenu2::draw()
{
    background.draw();
    gdata.window->draw(title);

    if (screen == 0)        mm_draw();
    else if (screen == 1)   om_draw();
    else if (screen == 2)   ls_draw();
}

void StateMenu2::mm_draw()
{
    // draw the menu
    int h = gdata.settings->getScreenHeight();
    int w = gdata.settings->getScreenWidth();
    for (int i = 0; i < mm_items.size(); ++i)
    {
        int x = w-ITEM_WIDTH;
        int y = h-BOTTOM_BUFFER-(mm_items.size()-i)*ITEM_SPACING;
        int indent = 0;

        if (i == mm_selected){
            //draw rectangle
            sf::RectangleShape rec(sf::Vector2f(BOX_WIDTH,ITEM_SPACING));
            rec.setPosition(x-10,y+5);
            rec.setFillColor(sf::Color::White);
            gdata.window->draw(rec);

            font.setColor(sf::Color::Black);
            indent = 20;
        }
        else
        {
            font.setColor(sf::Color::White);
            indent = 0;
        }

        font.drawString(x+indent,y,mm_items.at(i));
    }
}

void StateMenu2::om_draw()
{
        // draw the menu
    int h = gdata.settings->getScreenHeight();
    int w = gdata.settings->getScreenWidth();
    for (int i = 0; i < om_items.size(); ++i)
    {
        int x = w-ITEM_WIDTH;
        int y = h-BOTTOM_BUFFER-(om_items.size()-i)*ITEM_SPACING;
        int indent = 0;

        if (i == om_selected){
            //draw rectangle
            sf::RectangleShape rec(sf::Vector2f(BOX_WIDTH,ITEM_SPACING));
            rec.setPosition(x-10,y+5);
            rec.setFillColor(sf::Color::White);
            gdata.window->draw(rec);

            font.setColor(sf::Color::Black);
            indent = 20;
        }
        else
        {
            font.setColor(sf::Color::White);
            indent = 0;
        }

        font.drawString(x+indent,y,om_items.at(i));
    }
}

void StateMenu2::ls_draw()
{
    int w = gdata.settings->getScreenWidth();
    int h = gdata.settings->getScreenHeight();

    int sx = (152 * 9) + (25 * 8);
    int sy = 300;

    for (int row = 0; row < 4; ++row)
    for (int col = 0; col < 9; ++col)
    {
        if ( (row * 9 + col) < 35)
        {
            gdata.window->draw(icons[(row * 9) + col].rec);
        }
    }
}

void StateMenu2::freeResources()
{

}

