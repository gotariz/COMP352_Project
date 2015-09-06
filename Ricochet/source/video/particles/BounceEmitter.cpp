#include "BounceEmitter.h"

void BounceEmitter::createParticle()
{
    if (spawn)
   {
        BounceParticle* p = new BounceParticle();
        p->pos = pos;
        p->particle_dur = 500;
        particles.push_back(p);
        p->particle_create();
        spawn = false;
    }
}


