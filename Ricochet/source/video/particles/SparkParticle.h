#ifndef SPARKPARTICLE_H
#define SPARKPARTICLE_H

#include "general.h"
#include "system/GameData.h"
#include "Particle.h"
#include "objects/gObject.h"


class SparkParticle : public Particle, public gObject
{
    public:
        SparkParticle();
        virtual ~SparkParticle();

        int size = 0;
        sf::Color c = sf::Color::Red;

        virtual void particle_draw();
        virtual void particle_create();
        virtual void particle_update();
        virtual void particle_destroy();
};

#endif // SPARKPARTICLE_H
