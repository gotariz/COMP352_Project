#include "ExplosionParticle.h"

ExplosionParticle::ExplosionParticle()
{
    //ctor
}

ExplosionParticle::~ExplosionParticle()
{
    //dtor
}

void ExplosionParticle::particle_draw()
{
    Vector2 p = gdata.toScreenPixels(pos);
    img.setPosition(p.x,p.y);
    gdata.window->draw(img);
}

void ExplosionParticle::particle_create()
{
    img.setOrigin(285,400);
    d = utils::getRandom(1,2);
    speed = utils::getRandom(1,8);
    cout << d << endl;
}

void ExplosionParticle::particle_update()
{
    Particle::particle_update();
    float percent = static_cast<float>(particle_age) / static_cast<float>(particle_dur);


    float scale = ((0.3f * percent) + 0.1) * 2;
    if (scale > 0.4) scale = 0.4;


    img.setScale(scale,scale);
    c.a = static_cast<sf::Uint8>(255 - (255 * percent));
    img.setColor(c);

    if (d == 1) img.rotate( speed * gdata.m_timeDelta );
    else        img.rotate( -speed * gdata.m_timeDelta );
}

void ExplosionParticle::particle_destroy()
{

}

