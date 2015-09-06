#ifndef PARTICLE_H
#define PARTICLE_H

#include "system/GameData.h"
#include "IParticle.h"

class Particle : public IParticle
{
    public:
        Particle(){}
        virtual ~Particle(){}

        virtual void particle_draw() = 0;
        virtual void particle_create() = 0;
        virtual void particle_update();
        virtual void particle_destroy() = 0;
};

#endif // PARTICLE_H
