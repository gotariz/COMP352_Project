#include "BounceParticle.h"

void BounceParticle::particle_draw()
{
    float percent = (static_cast<float>(particle_age) / static_cast<float>(particle_dur));
    float size = (75 * gdata.zoom) * percent;

    Vector2 p = gdata.toScreenPixels(pos);
    c.setPosition(p.x,p.y);
    c.setRadius(size);
    c.setOrigin(size,size);
    c.setFillColor(sf::Color(255,255,255,0));
    c.setOutlineColor(sf::Color(255,255,255,255 * (1.f - percent)));
    gdata.window->draw(c);
}

void BounceParticle::particle_create()
{
    c.setOutlineThickness(2);
}

void BounceParticle::particle_update()
{
    particle_age += static_cast<int>(gdata.m_timeDelta * 1000.f);
}

void BounceParticle::particle_destroy()
{

}
