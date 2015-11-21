#include "Background.h"

void Background::init()
{

    rec.setSize(sf::Vector2f(38 * WORLD_SCALE * gdata.zoom,21 * WORLD_SCALE * gdata.zoom));
    rec.setOrigin(rec.getSize().x/2,rec.getSize().y/2);
    Vector2 p = gdata.toScreenPixels(0,0);
    rec.setPosition(p.x,p.y);

    for (int i = 0; i < num_circles; ++i)
    {
        bgCircle c;
        float x = utils::getRandom(0,38);
        float y = utils::getRandom(0,21);
        float dx = utils::getRandom(0,38);
        float dy = utils::getRandom(0,21);
        float r = utils::getRandom(10,100);
        float alpha = utils::getRandom(bubble_alpha_range.x,bubble_alpha_range.y);
        float speed = utils::getRandom(1,10);
        speed /= 20.f;
        r /= 100;
        x -= 18;
        y -= 10.5;
        dx -= 18;
        dy -= 10.5;

        c.speed = speed;
        c.dest.set(dx,dy);
        c.pos.set(x,y);
        c.radius= r;
        c.alpha = alpha;
        c.c.setPointCount(90);
        circles.push_back(c);
    }
}

void Background::draw()
{
    gdata.window->draw(rec);

    sf::Color c = sf::Color::White;
    c.a = 8;

     for (int x = -19; x <= 19; ++x)
    {
        Vector2 p1(x,10.5);
        Vector2 p2(x,-10.5);

        p1 = gdata.toScreenPixels(p1);
        p2 = gdata.toScreenPixels(p2);
        drawLine(p1,p2,c);
    }

    for (int y = -10; y <= 10; ++y)
    {
        Vector2 p1(-19,y);
        Vector2 p2(19,y);

        p1 = gdata.toScreenPixels(p1);
        p2 = gdata.toScreenPixels(p2);
        drawLine(p1,p2,c);
    }


    for (unsigned i = 0; i < circles.size(); ++i)
    {
        bgCircle* circle = &circles.at(i);

        Vector2 pos = gdata.toScreenPixels(circle->pos);
        circle->c.setRadius( circle->radius * WORLD_SCALE * gdata.zoom );
        circle->c.setPosition( pos.x,pos.y);
        circle->c.setFillColor(sf::Color(bubble_color.r,bubble_color.g,bubble_color.b,circle->alpha));
        gdata.window->draw(circle->c);
    }
}

void Background::update()
{
    rec.setSize(sf::Vector2f(gdata.settings->getScreenWidth(),gdata.settings->getScreenHeight()));
    rec.setOrigin(0,0);
    //Vector2 p = gdata.toScreenPixels(0,0);
    rec.setPosition(0,0);

    for (unsigned i = 0; i < circles.size(); ++i)
    {
        bgCircle* circle = &circles.at(i);

        // calculate how far you need to move
        Vector2 delta = circle->dest - circle->pos;
        float remaining_dist = delta.getMagnitude();
        float move_dist = circle->speed * gdata.m_timeDelta;
        if (move_dist >= remaining_dist)
        {
            circle->pos = circle->dest;
            float dx = utils::getRandom(0,38);
            float dy = utils::getRandom(0,21);
            dx -= 18;
            dy -= 10.5;
            circle->dest.set(dx,dy);
        }
        else
        {
            delta.setMagnitude(move_dist);
            circle->pos += delta;
        }
    }
}

void Background::drawLine(Vector2 p1, Vector2 p2, sf::Color c)
{
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(p1.x, p1.y),c),
        sf::Vertex(sf::Vector2f(p2.x, p2.y),c)
    };
    gdata.window->draw(line, 2, sf::Lines);
}

