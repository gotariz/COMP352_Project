#include "Player.h"

void Player::onUpdate()
{

//    for (int i = 0; i < trail.size(); ++i)
//    {
//        sf::CircleShape& circle = trail.at(i);
//        float a = circle.getFillColor().a;
//        a -= 255 * gdata.m_timeDelta;
//        if (a < 0) a = 0;
//        sf::Color nc = circle.getFillColor();
//        nc.a = a;
//        circle.setFillColor( nc );
//        float scale = circle.getScale().x;
//
//        scale -= 1.5 * gdata.m_timeDelta;
//        circle.setScale(scale,scale);
//    }
//
//    sf::CircleShape circle(0.5 * WORLD_SCALE * gdata.zoom);
//    sf::Color nc = c;
//    nc.a = 128;
//    circle.setFillColor(nc);
//    circle.setOrigin(circle.getRadius(),circle.getRadius());
//    Vector2 p = gdata.toPixels(getAbsolutePosition().x,getAbsolutePosition().y);
//    p.x -= gdata.camera->getScreenX();
//    p.y -= gdata.camera->getScreenY();
//    circle.setPosition(p.x,p.y);
//    trail.push_back(circle);


    if (c.r > 5)
    {
        c.r -= 165.f * gdata.m_timeDelta;
        if (c.r < 5)
        {
            c.r = 5;
        }
    }
//
//    if (c.g < 91)
//    {
//        c.g += 91.f * gdata.m_timeDelta;
//        if (c.g > 91)
//        {
//            c.g = 91;
//        }
//    }
//
//    for (int i = 0; i < circles.size(); ++i)
//    {
//        sf::CircleShape& circle = circles.at(i);
//
//        if (circle.getOutlineColor().a > 0)
//        {
//            circle.setRadius( circle.getRadius() + (WORLD_SCALE * 2 * gdata.m_timeDelta) );
//            circle.setOrigin(circle.getRadius(),circle.getRadius());
//
//            sf::Color color = circle.getOutlineColor();
//            int a = color.a;
//            a -=  255 * gdata.m_timeDelta;
//            if (a <= 0) color.a = 0;
//            else        color.a = a;
//
//
//            circle.setOutlineColor( color );
//        }
//        else
//        {
//            sf::Color color = circle.getFillColor();
//            color.a = 0;
//            circle.setOutlineColor(color);
//        }
//    }
}

void Player::onEnterCollision(CollisionData cd)
{
//    if (cd.points.size() > 0)
//    {
//        sf::CircleShape circle(0);
//        circle.setOutlineThickness(3);
//        circle.setFillColor(sf::Color::Transparent);
//        circle.setOutlineColor(sf::Color::White);
//        circle.setOrigin(circle.getRadius(),circle.getRadius());
//
//        Vector2 p = cd.points.at(0);
//        //p.print("cp:");
//        p = gdata.toPixels(p.x,p.y);
//		p.x -= gdata.camera->getScreenX();
//		p.y -= gdata.camera->getScreenY();
//        circle.setPosition(p.x,p.y);
//
//        circles.push_back(circle);
//    }
}

void Player::onCollision(Object* objectB)
{
    if (objectB->m_type == WALL)
    {
        float speed = getVelocity().getMagnitude();
        speed /= 25.0;
        c.r = 165 * speed;
        c.g = 91 - (91 * speed);
    }
}

void Player::onDraw()
{
    if (m_physicsObject != nullptr)
    {
		Vector2 pos = getAbsolutePosition();
		pos = gdata.toPixels(pos.x, pos.y);
		pos.x -= gdata.camera->getScreenX();
		pos.y -= gdata.camera->getScreenY();

		sf::CircleShape circle((0.5 * WORLD_SCALE) * gdata.zoom);
        circle.setFillColor(c);
        circle.setPosition(pos.x,pos.y);
        circle.setOrigin(circle.getRadius(),circle.getRadius());
        gdata.window->draw(circle);
    }

    for (int i = 0; i < circles.size(); ++i)
    {
        gdata.window->draw(circles.at(i));
    }

    for (int i = 0; i < trail.size(); ++i)
    {
        gdata.window->draw(trail.at(i));
    }
}
