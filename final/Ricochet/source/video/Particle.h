#ifndef PARTICLE_H
#define PARTICLE_H

#include "general.h"
#include "IParticle.h"
#include "objects/gObject.h"

class Particle : public IParticle, public gObject
{
    public:
        Vector2 pos;
        int size = 1;

        virtual void particle_draw();
        virtual void particle_create();
        virtual void particle_update();
        virtual void particle_destroy();
};

#endif // PARTICLE_H
