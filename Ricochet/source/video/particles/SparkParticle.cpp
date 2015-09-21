#include "SparkParticle.h"

SparkParticle::SparkParticle()
{
    //ctor
    m_type = PARTICLE;
}

SparkParticle::~SparkParticle()
{
    //dtor
}

void SparkParticle::particle_draw()
{
    Vector2 p = gdata.toScreenPixels(getAbsolutePosition());
    r.setPosition(p.x,p.y);
    gdata.window->draw(r);
}

void SparkParticle::particle_create()
{
    r.setSize(sf::Vector2f(size,size));
    r.setFillColor(c);
}

void SparkParticle::particle_update()
{
    Particle::particle_update();

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

void SparkParticle::particle_destroy()
{
    deletePhysicsObject();
}
