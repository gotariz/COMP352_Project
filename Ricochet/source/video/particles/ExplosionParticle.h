#ifndef EXPLOSIONPARTICLE_H
#define EXPLOSIONPARTICLE_H

#include "general.h"
#include "Particle.h"


class ExplosionParticle : public Particle
{
    public:
        ExplosionParticle();
        virtual ~ExplosionParticle();

        Vector2 pos;
        float scale_x = 0.1f;
        float scale_y = 0.1f;
        float opacity = 1.f;
        sf::Color c;
        int d = 1;
        float speed = 0;
        float ips = 1;
        float amount = 1;

        sf::Sprite  img;

        virtual void particle_draw();
        virtual void particle_create();
        virtual void particle_update();
        virtual void particle_destroy();
};

#endif // EXPLOSIONPARTICLE_H
