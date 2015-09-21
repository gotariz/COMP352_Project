#ifndef EXPLODEEMITTER_H
#define EXPLODEEMITTER_H

#include "ParticleEmitter.h"
#include "ExplodeParticle.h"


class ExplodeEmitter : public ParticleEmitter
{
    public:
        ExplodeEmitter();
        virtual ~ExplodeEmitter();

        int num_particles = 0;
        float min_size = 0;
        float max_size = 0;
        sf::Color c;
        Vector2 v;

        virtual void createParticle();
        virtual void drawParticles();
};

#endif // EXPLODEEMITTER_H
