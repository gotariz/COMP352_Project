#include "ParticleEmitter.h"


void ParticleEmitter::update()
{
    accumelator += gdata.m_timeDelta;
    particles.erase( remove_if(particles.begin(),particles.end(),condition), particles.end() );
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

