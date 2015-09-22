#include "Player.h"

void Player::freeResources()
{
    emitter.freeResources();
    explode_emitter.freeResources();
}

void Player::onCreate()
{
    color.setColor(5,91,165,255);
    color.setTime(0.5f);
    emitter.enabled = true;

    explode_emitter.num_particles = 200;
    explode_emitter.min_size = 0.05;
    explode_emitter.max_size = 0.15;
}

void Player::onUpdate()
{
    color.update(gdata.m_timeDelta);
    explode_emitter.c = color.getCurrentColor();
    emitter.update();
    explode_emitter.update();
}

void Player::onDestroy()
{
    explode_emitter.pos = getAbsolutePosition();
    explode_emitter.enabled = true;
    explode_emitter.v = getVelocity();
    draw_player = false;

    deletePhysicsObject();
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
        gdata.audio->playSound("bounce");

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

    if (m_physicsObject != nullptr && draw_player)
    {
        trail.setPlayerPosition(getAbsolutePosition());
        trail.draw();

		Vector2 pos = getAbsolutePosition();
		pos = gdata.toScreenPixels(pos.x, pos.y);
		sf::CircleShape circle((0.5 * WORLD_SCALE) * gdata.zoom);
        circle.setFillColor(color.getCurrentColor());
        circle.setPosition(pos.x,pos.y);
        circle.setOrigin(circle.getRadius(),circle.getRadius());

        gdata.window->draw(circle);
    }

    explode_emitter.drawParticles();
}
