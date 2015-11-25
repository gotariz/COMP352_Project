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

    mm_init();
    om_init();
    ls_init();

    if (!gdata.bg_music)
    {
        gdata.bg_music = gdata.audio->addMusic("Divider");
        gdata.bg_music->loop(true);
    }
}

void StateMenu2::applySettings()
{
    // apply resolution
    vector<string> resolution = gz::splitString(o_res.at(res_index),'x');
    int w = atoi(resolution.at(0).c_str());
    int h = atoi(resolution.at(1).c_str());
    gdata.settings->setScreenWidth(w);
    gdata.settings->setScreenHeight(h);
    gdata.window->setSize(sf::Vector2u(w,h));
    gdata.view = new sf::View(sf::FloatRect(0,0,w,h));
    gdata.window->setView(*gdata.view);
    // apply fullscreen
    gdata.settings->setFullscreen(fullscreen);
    // apply vsync
    gdata.settings->setVsync(vsync);
    gdata.window->setVerticalSyncEnabled(vsync);
    // apply fps limit
    gdata.settings->setFpsLimit(fps);
    gdata.window->setFramerateLimit(fps);
    // apply sfx volume
    gdata.settings->setSFX(sfx_vol);
    gdata.audio->setVolumeSFX(sfx_vol);
    // apply mus volume
    gdata.settings->setVolume(mus_vol);
    gdata.audio->setVolumeMusic(mus_vol);

    gdata.settings->saveSettings();
}

void StateMenu2::setApplied()
{
    for (int i = 0; i < o_res.size(); ++i)
    {
        string resolution = gz::toString(gdata.settings->getScreenWidth()) + "x" + gz::toString(gdata.settings->getScreenHeight());
        if (o_res.at(i) == resolution)
        {
            res_index = i;
        }
    }

    fullscreen = gdata.settings->getFullscreen();
    vsync = gdata.settings->getVsync();
    fps = gdata.settings->getFpsLimit();
    sfx_vol = gdata.audio->volume_sfx;
    mus_vol = gdata.audio->volume_music;
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
    int w = gdata.settings->getScreenWidth();
    int h = gdata.settings->getScreenHeight();

    next.setTexture(*gdata.assets->getTexture("arrow_idle"));
    prev.setTexture(*gdata.assets->getTexture("arrow_idle"));
    prev.setRotation(180);
    prev.setOrigin(33,65);

    om_items.push_back("Resolution");
    om_items.push_back("Screen Mode");
    om_items.push_back("V-Sync");
    om_items.push_back("FPS Limit");
    om_items.push_back("SFX Volume");
    om_items.push_back("Music Volume");
    om_items.push_back("Apply");
    om_items.push_back("Cancel");

    bool found = false;
    vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
    for (unsigned i = 0; i < modes.size(); i++)
    {
        sf::VideoMode mode = modes[i];
        o_res.push_back(gz::toString(mode.width) + "x" + gz::toString(mode.height));

        if (mode.width == w && mode.height == h)
        {
            res_index = i;
            found = true;
        }
    }
    reverse(o_res.begin(),o_res.end());
    res_index = o_res.size() - 1 - res_index;

    if (!found)
    {
        o_res.push_back(gz::toString(w) + "x" + gz::toString(h));
        res_index = o_res.size() - 1;
    }
}

void StateMenu2::ls_init()
{
    icons.clear();

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
        if (mm_selected == 0)       {screen = 2;ls_init();}// go to level select
        else if (mm_selected == 1)  ;// go to achievements
        else if (mm_selected == 2)  {screen = 1;setApplied();}// go to settings
        else if (mm_selected == 3)  gdata.running = false;// exit
    }

    if (gdata.keys[sf::Keyboard::Escape].isKeyPressed)
        gdata.running = false;
}

void StateMenu2::om_handleEvents()
{
    int h = gdata.settings->getScreenHeight();
    int w = gdata.settings->getScreenWidth();

    // next button
    int nx = next.getPosition().x;
    int ny = next.getPosition().y;
    int nw = next.getTexture()->getSize().x;
    int nh = next.getTexture()->getSize().y;
    //prev button
    int px = prev.getPosition().x;
    int py = prev.getPosition().y;
    int pw = prev.getTexture()->getSize().x;
    int ph = prev.getTexture()->getSize().y;

    bool clicked_next = utils::isTouching(gdata.mouse_raw,nx,ny,nw,nh) && gdata.keys[KEY_MOUSE_LEFT].isKeyPressed;
    bool clicked_prev = utils::isTouching(gdata.mouse_raw,px,py,pw,ph) && gdata.keys[KEY_MOUSE_LEFT].isKeyPressed;

    if (gdata.keys[sf::Keyboard::Up].isKeyPressed)
    {
        if (om_selected > 0) {--om_selected;}
    }
    if (gdata.keys[sf::Keyboard::Down].isKeyPressed)
    {
        if (om_selected < om_items.size()-1) {++om_selected;}
    }

    // handle mouse events (mouse over menu items)
    bool onItem = false;
    for (int i = 0; i < om_items.size(); ++i)
    {
        int x = w-ITEM_WIDTH;
        int y = h-BOTTOM_BUFFER-(om_items.size()-i)*ITEM_SPACING;

        if (i < om_items.size() - 2)
        {
            if (utils::isTouching(gdata.mouse_raw,x-OBOX_WIDTH - 20,y+5,BOX_WIDTH+OBOX_WIDTH+20,ITEM_SPACING))
            {
                om_selected = i;
                onItem = true;
            }
        }
        else
        {
            if (utils::isTouching(gdata.mouse_raw,x-20,y+5,BOX_WIDTH,ITEM_SPACING))
            {
                om_selected = i;
                onItem = true;
            }
        }
    }

    //clicking menu items
    if (gdata.keys[sf::Keyboard::Escape].isKeyPressed)  screen = 0;

    if (gdata.keys[sf::Keyboard::Left].isKeyPressed || clicked_prev)
    {
        if (om_selected == 0)
        {
            --res_index;
            if (res_index < 0){res_index = 0;}
        }
        else if (om_selected == 1) fullscreen = false;
        else if (om_selected == 2) vsync = false;
        else if (om_selected == 3) {fps -= 5;if(fps < 0) fps=0;}
        else if (om_selected == 4) {sfx_vol-=5;if (sfx_vol < 0) sfx_vol=0;}
        else if (om_selected == 5) {mus_vol-=5;if (mus_vol < 0) mus_vol=0;}
    }
    if (gdata.keys[sf::Keyboard::Right].isKeyPressed || clicked_next)
    {
        if (om_selected == 0)
        {
            ++res_index;
            if (res_index >= o_res.size()){res_index = o_res.size()-1;}
        }
        else if (om_selected == 1) fullscreen = true;
        else if (om_selected == 2) vsync = true;
        else if (om_selected == 3) ++fps;
        else if (om_selected == 4) {sfx_vol+=5;if (sfx_vol > 100) sfx_vol=100;}
        else if (om_selected == 5) {mus_vol+=5;if (mus_vol > 100) mus_vol=100;}
    }

    if (gdata.keys[sf::Keyboard::Return].isKeyPressed || (gdata.keys[KEY_MOUSE_LEFT].isKeyPressed && onItem))
    {
        if (om_selected == 6) {applySettings();}
        else if (om_selected == 7) {screen = 0;}
    }

    if (next_state != 2)
    {
        if (utils::isTouching(gdata.mouse_raw,nx,ny,nw,nh))
        {
            next.setTexture(*gdata.assets->getTexture("arrow_active"));
            next_state = 1;
        }
        else
        {
            next.setTexture(*gdata.assets->getTexture("arrow_idle"));
            next_state = 0;
        }
    }

    if (next_state != 2)
    {
        if (utils::isTouching(gdata.mouse_raw,px,py,pw,ph))
        {
            prev.setTexture(*gdata.assets->getTexture("arrow_active"));
            prev_state = 1;
        }
        else
        {
            prev.setTexture(*gdata.assets->getTexture("arrow_idle"));
            prev_state = 0;
        }
    }
}

void StateMenu2::ls_handleEvents()
{
    for (int i = 0; i < icons.size(); ++i)
    {
        bool touching = utils::isTouching(gdata.mouse_raw,icons.at(i).rec);
        icons.at(i).hover = touching;
        if (touching)   selected_level = i;
        if (icons.at(i).hover && gdata.keys[KEY_MOUSE_LEFT].isKeyPressed)
        {
            gdata.level = i + 1;
            gdata.gamestate = STATE_GAME;
        }

    }

    if (gdata.keys[sf::Keyboard::Return].isKeyPressed)
    {
        gdata.level = selected_level+1;
        gdata.gamestate = STATE_GAME;
    }

    if (gdata.keys[sf::Keyboard::Up].isKeyPressed)
    {
        if (selected_level - 9 >= 0)
            selected_level -= 9;
    }
    if (gdata.keys[sf::Keyboard::Down].isKeyPressed)
    {
        if (selected_level + 9 <= 35)
            selected_level += 9;
    }
    if (gdata.keys[sf::Keyboard::Left].isKeyPressed)
    {
        if (selected_level - 1 >= 0)
            selected_level -= 1;
    }
    if (gdata.keys[sf::Keyboard::Right].isKeyPressed)
    {
        if (selected_level + 1 < 35)
            selected_level += 1;
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
    icons.at(selected_level).hover = true;
    for (int i = 0; i < icons.size(); ++i)
    {
        icons.at(i).update();
    }
}

void StateMenu2::draw()
{
    background.draw();

    title.setPosition(gdata.settings->getScreenWidth() / 2,20);
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

            if (i < om_items.size() - 2)
            {
                sf::RectangleShape rec2(sf::Vector2f(OBOX_WIDTH,ITEM_SPACING));
                rec2.setPosition(x-OBOX_WIDTH - 20,y+5);
                rec2.setFillColor(sf::Color::White);
                gdata.window->draw(rec2);
                prev.setPosition(x-OBOX_WIDTH-20,y+5);
                gdata.window->draw(prev);
                next.setPosition(x-20-33,y+5);
                gdata.window->draw(next);
            }

            font.setColor(sf::Color::Black);
            indent = 20;
        }
        else
        {
            font.setColor(sf::Color::White);
            indent = 0;
        }

        font.drawString(x+indent,y,om_items.at(i));


        // some hard coding here
        string text = "";
        if (i == 0)
            text = o_res.at(res_index);
        else if (i == 1)
            text = fullscreen ? "fullscreen" : "windowed";
        else if (i == 2)
            text = vsync ? "on" : "off";
        else if(i == 3)
            text = gz::toString(fps);
        else if(i == 4)
            text = gz::toString(sfx_vol);
        else if(i == 5)
            text = gz::toString(mus_vol);

        font.drawString(x - 100,y,text,Align::RIGHT);
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

