#include "ProgressScreen.h"

void Button::init()
{
    txt.setWindow(gdata.window);
    txt.setFont(gdata.assets->getFont("segoe-ui-light-48"));
    txt.setColor(sf::Color::Black);
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

    btn_redo.c_idle = sf::Color(196,196,196);
    btn_redo.c_hover = sf::Color(175,175,175);

    btn_redo.setSize(250,90);
    btn_redo.setPosition((sw / 2) - 250,(sh / 2) + 110);
    btn_redo.init();
    btn_redo.name = "REDO";

    btn_next.c_idle = sf::Color(196,196,196);
    btn_next.c_hover = sf::Color(175,175,175);

    btn_next.setSize(250,90);
    btn_next.setPosition((sw / 2) + 1,(sh / 2) + 110);
    btn_next.init();
    btn_next.name = "NEXT";

    starbg.setTexture( *gdata.assets->getTexture("star_bg") );
    stars.setTexture( *gdata.assets->getTexture("stars") );
    thumbs.setTexture( *gdata.assets->getTexture("thumbs") );
    glow.setTexture( *gdata.assets->getTexture("glow") );

    starbg.setPosition((sw / 2) - 250,(sh / 2) + 25);
    stars.setPosition((sw / 2) - 250,(sh / 2) + 25);
    thumbs.setOrigin(87,74);
    thumbs.setPosition(sw/2,sh/2 - 55);
    glow.setOrigin(437,437);
    glow.setPosition(sw/2,sh/2 - 13);

    txt.setWindow(gdata.window);
    txt.setFont(gdata.assets->getFont("segoe-ui-light-48"));
    txt.setColor(sf::Color::Black);
}

void ProgressScreen::setStars(int n)
{
    int x = 501;
    if (n == 1)         x = 205;
    else if (n == 2)    x = 290;

    stars.setTextureRect(sf::IntRect(0,0,x,81));
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
    int sw = gdata.settings->getScreenWidth();
    int sh = gdata.settings->getScreenHeight();

    gdata.window->draw(glow);

    sf::RectangleShape rec(sf::Vector2f(501,400));
    rec.setFillColor(sf::Color(217,217,217));
    rec.setPosition((sw / 2) - 250, (sh / 2) - 200);

    sf::RectangleShape  seperator(sf::Vector2f(1,60));
    seperator.setFillColor(sf::Color(96,96,96));
    seperator.setPosition(sw/2, sh/2 + 125);

    sf::RectangleShape buttons(sf::Vector2f(501,90));
    buttons.setFillColor(sf::Color(196,196,196));
    buttons.setPosition((sw / 2) - 250,(sh / 2) + 110);


    gdata.window->draw(rec);
    gdata.window->draw(buttons);
    gdata.window->draw(seperator);

    txt.drawString((sw / 2), (sh / 2) - 165,"Level " + gz::toString(gdata.level) + " Complete!",Align::MIDDLE,Align::MIDDLE );

    gdata.window->draw(starbg);
    gdata.window->draw(stars);
    gdata.window->draw(thumbs);

    btn_redo.draw();
    btn_next.draw();
}

void ProgressScreen::handleEvents()
{
    btn_next.handleEvents();
    btn_redo.handleEvents();

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
}

