#include "Particle.h"

void Particle::particle_draw()
{
    Vector2 p = gdata.toScreenPixels(getAbsolutePosition());
    sf::RectangleShape r(sf::Vector2f(size,size));
    r.setPosition(p.x,p.y);
    r.setFillColor(sf::Color::Red);
    gdata.window->draw(r);

}

void Particle::particle_create()
{

}

void Particle::particle_update()
{
    particle_age += static_cast<int>(gdata.m_timeDelta * 1000.f);
}

void Particle::particle_destroy()
{
    deletePhysicsObject();
}

