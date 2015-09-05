#include "Particle.h"

void Particle::particle_draw()
{

}

void Particle::particle_create()
{

}

void Particle::particle_update()
{
    particle_age += static_cast<int>(gdata.m_timeDelta * 1000.f);
    if (particle_age > particle_dur) particle_age = particle_dur;
}

void Particle::particle_destroy()
{

}

