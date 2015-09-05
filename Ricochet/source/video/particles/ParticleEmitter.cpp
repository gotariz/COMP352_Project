#include "ParticleEmitter.h"


void ParticleEmitter::update()
{
    accumelator += gdata.m_timeDelta;

    // remove dead particles
    for (int i = 0; i < particles.size(); )
    {
        IParticle* p = particles.at(i);
        if (p->particle_age >= p->particle_dur)
        {
            particles.erase(particles.begin() + i);
            p->particle_destroy();
            delete p;
        }
        else
        {
            ++i;
        }
    }

    for (int i = 0; i < particles.size(); ++i)
    {
        particles.at(i)->particle_update();
    }

    if (enabled)    createParticle();

}

void ParticleEmitter::freeResources()
{
    for (int i = 0; i < particles.size(); ++i)
    {
        particles.at(i)->particle_destroy();
        delete particles.at(i);
    }

    particles.clear();
}

void ParticleEmitter::drawParticles()
{
    for (int i = 0; i < particles.size(); ++i)
    {
        particles.at(i)->particle_draw();
    }
}

