#include "ParticleEmitter.h"

void ParticleEmitter::createParticle()
{
    float t = (1.f / frequency);
    while (accumelator >= t)
    {
        float angle = utils::getRandom(0,180);
        angle -= 90;
        Particle* p = new Particle();
        p->pos.set(pos);
        p->particle_dur = duration;
        p->setPhysicsObject(gdata.factory->createParticle(p->pos.x,p->pos.y));

        Vector2 vel = dir;
        vel.rotate(angle);
        vel.setMagnitude(speed);
        p->setLinearVelocity(vel);

        particles.push_back(p);
        accumelator -= t;
    }
}

void ParticleEmitter::update()
{
    accumelator += gdata.m_timeDelta;
    particles.erase( remove_if(particles.begin(),particles.end(),condition), particles.end() );
    for (int i = 0; i < particles.size(); ++i)
    {
        particles.at(i)->particle_update();
    }
    createParticle();

}

void ParticleEmitter::freeResources()
{
    for (int i = 0; i < particles.size(); ++i)
    {
        delete particles.at(i);
    }

    particles.clear();
}

bool ParticleEmitter::condition(IParticle* p)
{
    bool del = (p->particle_age >= p->particle_dur);
    if (del)
    {
        p->particle_destroy();
    }
    return del;
}

void ParticleEmitter::drawParticles()
{
    for (int i = 0; i < particles.size(); ++i)
    {
        particles.at(i)->particle_draw();
    }
}

