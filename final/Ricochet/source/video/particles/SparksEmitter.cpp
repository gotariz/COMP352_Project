#include "SparksEmitter.h"

void SparksEmitter::createParticle()
{
    float t = (1.f / frequency);
    while (accumelator >= t)
    {
        float angle         = utils::getRandom(0,180) - 90;
        Vector2 vel         = dir;

        vel.rotate(angle);
        vel.setMagnitude(speed);

        SparkParticle* p = new SparkParticle();

        p->particle_age = 0;
        p->particle_dur = duration;
        p->size = size;
        p->setPhysicsObject(gdata.factory->createParticle(pos.x,pos.y));
        p->setLinearVelocity(vel);

        particles.push_back(p);
        accumelator -= t;
    }
}
