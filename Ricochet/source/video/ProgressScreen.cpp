#include "ProgressScreen.h"

void Button::init()
{
    txt.setWindow(gdata.window);
    txt.setFont(gdata.assets->getFont("purista-medium-14"));
    txt.setColor(sf::Color::Black);

    rec.setOutlineThickness(1);
    rec.setOutlineColor(sf::Color::Black);

    b_idle = c_idle;
    b_hover = c_hover;

    b_idle.r -= 40;
    b_idle.g -= 40;
    b_idle.b -= 40;

    b_hover.r -= 20;
    b_hover.g -= 20;
    b_hover.b -= 20;
}

void Button::handleEvents()
{
    if (isTouching(gdata.mouse_raw))
    {
        rec.setFillColor(c_hover);
        if (gdata.keys[KEY_MOUSE_LEFT].isKeyPressed)
        {
            clicked = true;
        }
    }
    else
    {
        rec.setFillColor(c_idle);
    }
}

void Button::draw()
{
    gdata.window->draw(rec);

    int tx = rec.getPosition().x + (rec.getSize().x / 2);
    int ty = rec.getPosition().y + (rec.getSize().y / 2);
    txt.drawString(tx,ty,name,Align::MIDDLE,Align::MIDDLE);
}

void Button::setPosition(int x, int y)
{
    rec.setPosition(x,y);
}

void Button::setSize(int w, int h)
{
    rec.setSize(sf::Vector2f(w,h));
}

bool Button::isTouching(Vector2 point)
{
    if (point.x < rec.getPosition().x) return false;
    if (point.y < rec.getPosition().y) return false;

    if (point.x > rec.getPosition().x + rec.getSize().x - 1) return false;
    if (point.y > rec.getPosition().y + rec.getSize().y - 1) return false;

    return true;
}


//===================================================================================================
ProgressScreen::ProgressScreen()
{
    //ctor
}

ProgressScreen::~ProgressScreen()
{
    //dtor
}

void ProgressScreen::init()
{
    int sw = gdata.settings->getScreenWidth();
    int sh = gdata.settings->getScreenHeight();

    int cx = sw / 2;
    int cy = sh / 2;

    int w  = 460;
    int h  = 280;
    int tx = cx - (w / 2);
    int ty = cy - (h / 2);

    int btn_y = ty + h - 55;

    sf::Color idle = sf::Color(210,210,210);
    sf::Color hover = sf::Color(0,153,255);

    btn_redo.c_idle = idle;
    btn_redo.c_hover = hover;

    btn_redo.setSize(140,45);
    btn_redo.setPosition(tx + 10,btn_y);
    btn_redo.init();
    btn_redo.name = "REDO";

    btn_menu.c_idle = idle;
    btn_menu.c_hover = hover;

    btn_menu.setSize(140,45);
    btn_menu.setPosition(tx + 160,btn_y);
    btn_menu.init();
    btn_menu.name = "WATCH REPLAY";

    btn_next.c_idle = idle;
    btn_next.c_hover = hover;

    btn_next.setSize(140,45);
    btn_next.setPosition(tx + 310,btn_y);
    btn_next.init();
    btn_next.name = "NEXT";

    glow.setTexture( *gdata.assets->getTexture("glow") );

    glow.setOrigin( glow.getTexture()->getSize().x/2,glow.getTexture()->getSize().y/2);
    glow.setPosition(sw/2,sh/2);

    txt.setWindow(gdata.window);
    txt.setFont(gdata.assets->getFont("segoe-ui-light-48"));
    txt.setColor(sf::Color::White);

    lvl_complete.setTexture( *gdata.assets->getTexture("level_complete") );

    s_bronze.setTexture(*gdata.assets->getTexture("bronze"));
    s_silver.setTexture(*gdata.assets->getTexture("silver"));
    s_gold.setTexture(*gdata.assets->getTexture("gold"));

    s_bronze.setOrigin(75,121);
    s_silver.setOrigin(75,121);
    s_gold.setOrigin(75,121);

    s_bronze.setPosition(cx - 152,cy + 35);
    s_silver.setPosition(cx,cy + 35);
    s_gold.setPosition(cx + 152,cy + 35);



    lvl_complete.setPosition(cx - 176,ty + 10);
}

void ProgressScreen::setStars(int n, int b)
{
    stars = n;
    bounces = b;
//    if (n == 1)
//    else if (n == 2)
//    else if (n == 3)
}

void ProgressScreen::update()
{
    float range = 192;
    float time = 1.f;
    float transparency = 255 - range;

    if (fading) elapsed -= gdata.m_timeDelta;
    else        elapsed += gdata.m_timeDelta;

    if (elapsed >= time)
    {
        elapsed = time;
        fading = true;
    }
    else if (elapsed <= 0)
    {
        elapsed = 0;
        fading = false;
    }

    transparency += range * (elapsed / time);

    glow.setColor(sf::Color(255,255,255,transparency));

}

void ProgressScreen::draw()
{
    int cx = gdata.settings->getScreenWidth() / 2;
    int cy = gdata.settings->getScreenHeight() / 2;

    gdata.window->draw(glow);

    int w  = 460;
    int h  = 280;
    int tx = cx - (w / 2);
    int ty = cy - (h / 2);

    sf::RectangleShape rec(sf::Vector2f(w,h));
    rec.setFillColor(sf::Color(38,38,38));
    rec.setPosition(cx - (w/2), cy - (h/2));
    rec.setOutlineThickness(1);
    rec.setOutlineColor(sf::Color::Black);

    sf::RectangleShape  seperator(sf::Vector2f(460,1));
    seperator.setFillColor(sf::Color::Black);
    seperator.setPosition(cx - 230, ty + h - 66);

    sf::RectangleShape  b_section(sf::Vector2f(460,65));
    b_section.setFillColor(sf::Color(60,60,60));
    b_section.setPosition(tx, ty + h - 65);

    gdata.window->draw(rec);
    gdata.window->draw(b_section);
    gdata.window->draw(seperator);

    btn_redo.draw();
    btn_next.draw();
    btn_menu.draw();

    gdata.window->draw(lvl_complete);
    //gdata.window->draw(score_bar);

//    txt.setColor(sf::Color::White);
//    txt.drawString(cx,cy - 10,"Bounces: " + gz::toString(gdata.bounce_counter),Align::MIDDLE, Align::BOTTOM);

    sf::RectangleShape r(sf::Vector2f(140,15));
    r.setFillColor(sf::Color(0,153,255));

    gdata.window->draw(s_bronze);
    gdata.window->draw(s_silver);
    gdata.window->draw(s_gold);

    int st = 255;
    int gt = 255;
    if (stars == 1)
    {
        s_silver.setColor(sf::Color(255,255,255,24));
        s_gold.setColor(sf::Color(255,255,255,24));
        st = 32;
        gt = 32;
    }
    if (stars == 2)
    {
        s_silver.setColor(sf::Color(255,255,255,255));
        s_gold.setColor(sf::Color(255,255,255,24));
        st = 255;
        gt = 32;
    }
    if (stars == 3)
    {
        s_silver.setColor(sf::Color(255,255,255,255));
        s_gold.setColor(sf::Color(255,255,255,255));
        st = 255;
        gt = 255;
    }

    txt.setColor(sf::Color::Black);
    txt.setTransparency(st);
    txt.drawString(cx,ty+95,gz::toString(two_star),Align::MIDDLE);
    txt.setTransparency(gt);
    txt.drawString(cx+152,ty+95,gz::toString(one_star),Align::MIDDLE);
}

void ProgressScreen::handleEvents()
{
    btn_next.handleEvents();
    btn_redo.handleEvents();
    btn_menu.handleEvents();

    if (btn_next.clicked)
    {
        gdata.reload = true;
        ++gdata.level;
        gdata.first_shot = true;
        btn_next.clicked = false;
        gdata.show_progress = false;
        gdata.audio->playSound("click");
        gdata.replay_level = false;
        gdata.shotData.clear();
    }

    if (btn_redo.clicked)
    {
        gdata.reload = true;
        gdata.first_shot = true;
        btn_redo.clicked = false;
        gdata.show_progress = false;
        gdata.replay_level = false;
        gdata.audio->playSound("click");
        gdata.shotData.clear();
    }

    if (btn_menu.clicked)
    {
        gdata.reload = true;
        gdata.replay_level = true;
        // go back to main menu
//        gdata.gamestate = STATE_MENU;
//        btn_menu.clicked = false;
        gdata.show_progress = false;
        gdata.audio->playSound("click");
    }
}

