#include "BounceEmitter.h"

void BounceEmitter::createParticle()
{
    if (spawn)
   {
        pos.print("pos");
        BounceParticle* p = new BounceParticle();
        p->pos = pos;
        p->particle_dur = 500;
        particles.push_back(p);
        spawn = false;
    }
}
