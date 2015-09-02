#include "SparksEmitter.h"

void SparksEmitter::createParticle()
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
