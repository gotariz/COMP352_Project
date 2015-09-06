#include "Player.h"

void Player::onCreate()
{
    color.setColor(5,91,165,255);
    color.setTime(0.5f);
    emitter.enabled = true;
}

void Player::onUpdate()
{
    color.update(gdata.m_timeDelta);
    emitter.update();
}

void Player::onEnterCollision(CollisionData cd)
{
    if (cd.points.size() > 0)
    {
        if (cd.objectB->m_type != PARTICLE)
        {
            emitter.spawn = true;
            emitter.pos = cd.points.at(0);
            trail.addPoint(getAbsolutePosition());
        }
    }
}

void Player::onCollision(Object* objectB)
{
    if (objectB->m_type == WALL)
    {
        float speed = getVelocity().getMagnitude();
        speed /= maxSpeed;
        int r = 165 * speed;
        int g = 91 - (91 * speed);
        int b = 165;

        r = (r > 165) ? 165 : r;
        g = (g < 0) ? 0 : g;

        color.setColor2(r,g,165,255);
        color.reset();
        color.start();

        trail.length = MAX_TAIL_LENGTH * (getVelocity().getMagnitude() / maxSpeed);
    }
}

void Player::onPostPhysicsUpdate()
{
    Vector2 vel = getVelocity();
    if (vel.x != 0 && vel.y != 0)
    {
        vel.setMagnitude(currentSpeed);
        setLinearVelocity(vel);
    }
}

void Player::onDraw()
{
    emitter.drawParticles();
    trail.setPlayerPosition(getAbsolutePosition());
    trail.draw();

    if (m_physicsObject != nullptr)
    {
		Vector2 pos = getAbsolutePosition();
		pos = gdata.toScreenPixels(pos.x, pos.y);
		sf::CircleShape circle((0.5 * WORLD_SCALE) * gdata.zoom);
        circle.setFillColor(color.getCurrentColor());
        circle.setPosition(pos.x,pos.y);
        circle.setOrigin(circle.getRadius(),circle.getRadius());

        circle.setOutlineThickness(1);
        circle.setOutlineColor(sf::Color::Black);

        gdata.window->draw(circle);
    }
}































