#include "BounceParticle.h"

void BounceParticle::particle_draw()
{
    float percent = (static_cast<float>(particle_age) / static_cast<float>(particle_dur));
    float size = (75 * gdata.zoom) * percent;
    sf::CircleShape c(size);

    Vector2 p = gdata.toScreenPixels(pos);
    c.setOrigin(size,size);
    c.setPosition(p.x,p.y);
    c.setFillColor(sf::Color(255,255,255,255 * (1.f - percent)));// * (1.f - percent)));
    gdata.window->draw(c);
}

void BounceParticle::particle_create()
{

}

void BounceParticle::particle_update()
{
    particle_age += static_cast<int>(gdata.m_timeDelta * 1000.f);
}

void BounceParticle::particle_destroy()
{

}
