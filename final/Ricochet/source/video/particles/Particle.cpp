#include "Particle.h"

void Particle::particle_draw()
{
    Vector2 p = gdata.toScreenPixels(getAbsolutePosition());
    sf::RectangleShape r(sf::Vector2f(size,size));
    r.setPosition(p.x,p.y);
    r.setFillColor(c);
    gdata.window->draw(r);
}

void Particle::particle_create()
{

}

void Particle::particle_update()
{
    particle_age += static_cast<int>(gdata.m_timeDelta * 1000.f);
    if (particle_age > particle_dur) particle_age = particle_dur;

    float percent_old = (static_cast<float>(particle_age) / static_cast<float>(particle_dur));
    float fade_age = 0.7;
    if (percent_old >= fade_age)
    {
        percent_old -= fade_age;
        percent_old /= 1.f - fade_age;
        percent_old = 1.f - percent_old;
        float alpha = 255 * percent_old;
        c = sf::Color(255,0,0,alpha);
    }
}

void Particle::particle_destroy()
{
    deletePhysicsObject();
}

