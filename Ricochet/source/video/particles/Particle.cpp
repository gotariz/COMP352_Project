#include "Particle.h"

void Particle::particle_update()
{
    particle_age += static_cast<int>(gdata.m_timeDelta * 1000.f);
    if (particle_age > particle_dur) particle_age = particle_dur;
}


