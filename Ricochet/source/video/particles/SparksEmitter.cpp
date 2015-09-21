#include "SparksEmitter.h"

void SparksEmitter::createParticle()
{
    float t = (1.f / frequency);
    while (accumelator >= t)
    {
        float angle = utils::getRandom(0,18000);
        angle /= 100;
        angle -= 90;
        SparkParticle* p = new SparkParticle();
        p->pos.set(pos);
        p->particle_dur = duration;
        p->size = size;
        p->setPhysicsObject(gdata.factory->createParticle(p->pos.x,p->pos.y,p));
        p->particle_create();

        Vector2 vel = dir;
        vel.rotate(angle);
        vel.setMagnitude(speed);
        p->setLinearVelocity(vel);

        particles.push_back(p);
        accumelator -= t;
    }
}
