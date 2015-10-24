#include "ProgressScreen.h"

void Button::init()
{
    txt.setWindow(gdata.window);
    txt.setFont(gdata.assets->getFont("purista-medium-14"));
    txt.setColor(sf::Color::Black);

    rec.setOutlineThickness(1);

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
        rec.setOutlineColor(b_hover);
        if (gdata.keys[KEY_MOUSE_LEFT].isKeyPressed)
        {
            clicked = true;
        }
    }
    else
    {
        rec.setFillColor(c_idle);
        rec.setOutlineColor(b_idle);
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

    btn_redo.c_idle = sf::Color(210,210,210);
    btn_redo.c_hover = sf::Color(25,155,240);

    btn_redo.setSize(140,45);
    btn_redo.setPosition((sw / 2) - 220,(sh / 2) + 145);
    btn_redo.init();
    btn_redo.name = "REDO";

    btn_next.c_idle = sf::Color(210,210,210);
    btn_next.c_hover = sf::Color(25,155,240);

    btn_next.setSize(140,45);
    btn_next.setPosition((sw / 2) + 80,(sh / 2) + 145);
    btn_next.init();
    btn_next.name = "NEXT";

    btn_menu.c_idle = sf::Color(210,210,210);
    btn_menu.c_hover = sf::Color(25,155,240);

    btn_menu.setSize(140,45);
    btn_menu.setPosition((sw / 2) - 70,(sh / 2) + 145);
    btn_menu.init();
    btn_menu.name = "MAIN MENU";

    star.setTexture( *gdata.assets->getTexture("star") );
    glow.setTexture( *gdata.assets->getTexture("glow") );

    star.setPosition(sw / 2,sh / 2);
    star.setOrigin(68,63);

    glow.setOrigin( glow.getTexture()->getSize().x/2,glow.getTexture()->getSize().y/2);
    glow.setPosition(sw/2,sh/2);

    txt.setWindow(gdata.window);
    txt.setFont(gdata.assets->getFont("elemental-end-30"));
    txt.setColor(sf::Color::Black);
}

void ProgressScreen::setStars(int n, int b, int min_b)
{
    stars = n;
    bounces = b;
    min_bounces = min_b;
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

    sf::RectangleShape rec(sf::Vector2f(460,400));
    rec.setFillColor(sf::Color(255,255,255));
    rec.setPosition(cx - 230, cy - 200);

    sf::RectangleShape  seperator(sf::Vector2f(460,1));
    seperator.setFillColor(sf::Color(200,200,200));
    seperator.setPosition(cx - 230, cy + 134);

    sf::RectangleShape  b_section(sf::Vector2f(460,65));
    b_section.setFillColor(sf::Color(230,230,230));
    b_section.setPosition(cx - 230, cy + 135);

    gdata.window->draw(rec);
    gdata.window->draw(b_section);
    gdata.window->draw(seperator);

    txt.setFont(gdata.assets->getFont("elemental-end-30"));
    txt.setColor(sf::Color::Black);
    txt.drawString(cx, cy - 170,"Level " + gz::toString(gdata.level) + " Complete!",Align::MIDDLE,Align::MIDDLE );

    int sy = cy + 50;
    if (stars == 1)
    {
        star.setPosition(cx,sy);
        gdata.window->draw(star);
    }
    else if (stars == 2)
    {
        // left
        star.setPosition(cx - 75,sy);
        gdata.window->draw(star);

        // right
        star.setPosition(cx + 75,sy);
        gdata.window->draw(star);
    }
    else if (stars == 3)
    {
        // left
        star.setPosition(cx - 145,sy);
        gdata.window->draw(star);

        // center
        star.setPosition(cx,sy);
        gdata.window->draw(star);

        // right
        star.setPosition(cx + 145,sy);
        gdata.window->draw(star);
    }

    //txt.setFont(gdata.assets->getFont("segoe-ui-light-48"));

    txt.setColor(sf::Color(128,128,128));
    txt.drawString(cx, cy - 120,gz::toString(bounces) + (bounces == 1 ? " bounce" : " bounces"),Align::MIDDLE);
    txt.drawString(cx, cy - 90,"3 star = " + gz::toString(min_bounces),Align::MIDDLE);


    btn_redo.draw();
    btn_next.draw();
    btn_menu.draw();
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
    }

    if (btn_redo.clicked)
    {
        gdata.reload = true;
        gdata.first_shot = true;
        btn_redo.clicked = false;
        gdata.show_progress = false;
        gdata.audio->playSound("click");
    }

    if (btn_menu.clicked)
    {
        // go back to main menu
        gdata.gamestate = STATE_MENU;
        btn_menu.clicked = false;
        gdata.show_progress = false;
        gdata.audio->playSound("click");
    }
}

