#include "Background.h"

void Background::init()
{
    bg_image.setOrigin(960,540);
    //bg_image.setColor( sf::Color(5,40,28,255) );


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
        speed /= 10.f;
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
        c.c.setPointCount(360);
        circles.push_back(c);
    }
}

void Background::draw()
{
    Vector2 pos = gdata.toScreenPixels(position);
    bg_image.setPosition(pos.x,pos.y);
    bg_image.setScale(gdata.zoom,gdata.zoom);
    gdata.window->draw(bg_image);

    for (int i = 0; i < circles.size(); ++i)
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
    for (int i = 0; i < circles.size(); ++i)
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

