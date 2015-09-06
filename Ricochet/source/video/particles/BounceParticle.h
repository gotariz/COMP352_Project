#ifndef BOUNCEPARTICLE_H
#define BOUNCEPARTICLE_H

#include "general.h"
#include "system/GameData.h"
#include "Particle.h"


class BounceParticle : public Particle
{
    public:
        BounceParticle(){}
        virtual ~BounceParticle(){}

        sf::CircleShape c;

        virtual void particle_draw();
        virtual void particle_create();
        virtual void particle_destroy();
};

#endif // BOUNCEPARTICLE_H
