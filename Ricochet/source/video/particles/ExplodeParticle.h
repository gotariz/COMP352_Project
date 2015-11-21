#ifndef EXPLODEPARTICLE_H
#define EXPLODEPARTICLE_H

#include "objects/gObject.h"
#include "Particle.h"


class ExplodeParticle : public Particle, public gObject
{
    public:
        ExplodeParticle();
        virtual ~ExplodeParticle();

        float size = 0;
        sf::Color c;
        sf::CircleShape circle;

        virtual void particle_draw();
        virtual void particle_create();
        virtual void particle_destroy();

        virtual void onDraw();
};

#endif // EXPLODEPARTICLE_H
